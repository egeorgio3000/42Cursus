#include "TCPserver.hpp"

TCPserver::TCPserver(int const& port, std::string const& password)
    : _master_socket(), _pfds(), _password(password), _port(port), _buffer() { }

TCPserver::~TCPserver() { }

/* Getters */
Channel& TCPserver::getChannel(std::string const& name) {
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->getName() == name)
            return *it;
    }
    _channels.push_back(Channel(name));
    return _channels.back();
}

User& TCPserver::getUser(int const& user_fd) {
    std::map<int, User>::iterator it = _users.find(user_fd);
    if (it != _users.end())
        return it->second;
    throw std::runtime_error("User not found");
}

/* Utils */
bool TCPserver::isChannelNameValid(std::string const& channelName) {
    if (channelName.length() < 2 || channelName.length() > MAX_CHANNEL_SIZE) return false;
    if (channelName[0] != '#' && channelName[0] != '&') return false;

    for (std::string::size_type i(1); i < channelName.length(); i++) {
        if (!std::isalnum(channelName[i])
            || channelName[i] == ' '
            || channelName[i] == ',')
            return false;
    }
    return true;
}

bool TCPserver::isChannelNameTaken(std::string const& channelName) {
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->getName() == channelName)
            return true;
    }
    return false;
}

/* core */
void TCPserver::runServer() {
    /* Create a master_socket */
    TCPsocket master_socket(_port);

    /* try to specify maximum of MAX_CONNECTIONS for the master socket */
    if (listen(master_socket.getFD(), MAX_CONNECTIONS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << displayTimestamp() << "Waiting for connections on port: [" << _port << "]" << std::endl;

    /* Client address */
    SOCKET new_sd;

    /* Initialize the pollfd structure */
    _pfds.push_back(pollfd());
    _pfds.back().fd = master_socket.getFD();
    _pfds.back().events = POLLIN;

    /* loop through all sockets and check which ones are ready to be read from */
    while (poll(_pfds.data(), _pfds.size(), -1) != -1) {
        /* print server info */
        std::cout << displayTimestamp() << "[INFO] Number of users connected: [" << _users.size() << "]" << std::endl;
        std::cout << displayTimestamp() << "[INFO] Number of channels created: [" << _channels.size() << "]" << std::endl;
        if (DEBUG) {
            /* print all channels and their operators */
            for (std::string::size_type i(0); i < _channels.size(); i++) {
                std::cout << displayTimestamp() << "[DEBUG] Channel: [" << _channels[i].getName() << "] has operators: ";
                for (std::string::size_type j(0); j < _channels[i].getOperators().size(); j++) {
                    std::cout << "[" << _channels[i].getOperators()[j] << "] ";
                }
            }
            std::cout << std::endl;
        }
        for (std::vector<pollfd>::size_type i(0); i < _pfds.size(); i++) {
            /* clear garbage in buffer */
            memset(_buffer, 0, BUFFER_SIZE);
            /* If socket is readable, handle data */
            if (_pfds[i].revents & POLLIN
                //|| _pfds[i].revents & POLLPRI // v ne fonctionnent pas wlh
                //|| _pfds[i].revents & POLLRDHUP
                //|| _pfds[i].revents & POLLHUP
                //|| _pfds[i].revents & POLLERR
            ) {
                /* If master socket pfds[0] is readable, handle new connection */
                if (i == 0) {
                    if ((new_sd = accept(master_socket.getFD(), NULL, NULL)) < 0) {
                        perror("accept failed");
                        break;
                    }
                    std::cout << displayTimestamp() << "[INFO] New connection on socket: [" << new_sd << "]" << std::endl;
                    /* Add new connection to pollfd structure */
                    _pfds.push_back(pollfd());
                    _pfds.back().fd = new_sd;
                    _pfds.back().events = POLLIN;
                    /* Add new connection to user map */
                    _users[new_sd] = User(new_sd);
                } else {
                    /* Handle data from client */
                    int bytes_read = recv(_pfds[i].fd, _buffer, sizeof(_buffer), 0);
                    std::cout << displayTimestamp() << "[INFO] bytes read from socket: [" << _pfds[i].fd << "]: " << bytes_read << std::endl;
                    /* If connection is closed, close socket and remove from pollfd structure */
                    if (bytes_read <= 0) {
                        deleteUser(i);
                    } else {
                        /* If connection is open, handle data */
                        /* print buffer */
                        std::cout << displayTimestamp() << "[INCOMING] Socket[" << _pfds[i].fd << "]: " << _buffer;
                        /* Split buffer into user's _commands */
                        std::vector<std::string> commands = split(_buffer, "\r\n");
                        for (std::vector<std::string>::size_type j(0); j < commands.size(); j++) {
                            if (commands[j].size() > 0) {
                                _users[_pfds[i].fd].addCommand(commands[j]);
                            }
                        }
                        /* Print user's _commands for debugging purpose */
                        if (DEBUG) { _users[_pfds[i].fd].printCommands(); }
                        /* if user is not registered, handle registration */
                        if (!_users[_pfds[i].fd].isRegistered()) { registerUser(_users[_pfds[i].fd]); }
                        /* if user registration ended but authentication failed, close connection */
                        if (_users[_pfds[i].fd].isRegistered() && !_users[_pfds[i].fd].isAuthenticated()) { deleteUser(i); }
                        /* if user is registered and authenticated, handle client commands */
                        if (_users[_pfds[i].fd].isRegistered() && _users[_pfds[i].fd].isAuthenticated()) { handleClientCommands(_users[_pfds[i].fd]); }
                    }
                }
            }
        }
        for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
            if (it->getUsers().size() == 0) {
                _channels.erase(it);
                break;
            }
        }
    }
}

/* handle user's _commands */
/**
 * CAP command:
 * https://modern.ircdocs.horse/#cap-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent to the server.
 */
void TCPserver::handleCAP(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        user.deleteCommand("CAP");
        /* as CAP is not handled, we just send a 421 error */
        std::string reply = std::string(ERR_UNKNOWNCOMMAND) + " " + command[0] + " :CAP not supported by server\r\n";
        sendReply(user, reply);
    }
}

/**
 * PASS command:
 * https://modern.ircdocs.horse/#pass-message
 *
 * @param user a reference to the User object that is currently logged in
 * @param password the password the user entered
 */
void TCPserver::handlePASS(User& user, std::string const& password) {
    if (password.size() > 0) {
        if (password == _password) {
            std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: valid password" << std::endl;
            user.deleteCommand("PASS");
            user.setAuthenticated(TRUE);
        } else {
            std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: invalid password " << std::endl;
            std::string message = std::string(ERR_PASSWDMISMATCH) + " : ERROR :Invalid Password\r\n";
            sendReply(user, message);
            user.setAuthenticated(FALSE);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : ERROR :This server is password protected\r\n";
        sendReply(user, message);
        user.setAuthenticated(FALSE);
    }
}

/**
 * NICK command:
 * https://modern.ircdocs.horse/#nick-message
 *
 * @param user The user who sent the command.
 * @param command a vector of strings, where each string is a word in the command.
 */
void TCPserver::handleNICK(User& user, std::string const& nickname) {
    if (nickname.size() > 0) {
        std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: requesting nickname " << nickname << std::endl;
        if (isNicknameValid(nickname) && nickname != SERVER_NAME) {
            /* check if nickname is already taken in the server's _user map */
            std::string nickname_ = nickname;
            while (isNicknameTaken(nickname_, _users)) {
                nickname_ += "_";
            }
            /* if nickname is not taken, set it */
            user.setNickname(nickname_);
            std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: nickname set to " << user.getNickname() << std::endl;
            user.deleteCommand("NICK");
        } else {
            /* if nickname is not valid, send error message */
            std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + nickname + " :Erroneous nickname\r\n";
            sendReply(user, message);
            user.setAuthenticated(FALSE);
        }
    } else {
        /* if nickname is empty, send error message */
        std::string message = std::string(ERR_NONICKNAMEGIVEN) + " :No nickname given\r\n";
        sendReply(user, message);
        user.setAuthenticated(FALSE);
    }
}

void TCPserver::changeNICK(User& user, std::string const& nickname) {
    if (nickname.size() > 0) {
        std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: requesting nickname " << nickname << std::endl;
        if (isNicknameValid(nickname) && nickname != SERVER_NAME) {
            /* check if nickname is already taken in the server's _user map */
            if (isNicknameTaken(nickname, _users)) {
                std::string message = std::string(ERR_NICKNAMEINUSE) + " " + nickname + " :\r\n";
                sendReply(user, message);
                user.deleteCommand("NICK");
                return;
            }
            /* if nickname is not taken, set it */
            std::string oldnickname = user.getNickname();
            user.setNickname(nickname);
            std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: nickname set to " << user.getNickname() << std::endl;
            std::string message = ":" + oldnickname + "!" + user.getUsername() + "@" + user.getHostname() + " NICK " + user.getNickname() + "\r\n";
            sendReply(user, message);
            user.deleteCommand("NICK");
        } else {
            /* if nickname is not valid, send error message */
            std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + nickname + " :Erroneous nickname\r\n";
            sendReply(user, message);
            user.setAuthenticated(FALSE);
        }
    } else {
        /* if nickname is empty, send error message */
        std::string message = std::string(ERR_NONICKNAMEGIVEN) + " :No nickname given\r\n";
        sendReply(user, message);
        user.setAuthenticated(FALSE);
    }
}

/**
 * USER command:
 * https://modern.ircdocs.horse/#user-message
 *
 * @param user a reference to the user object that is currently connected to the server
 * @param command a vector of strings, where each string is a word in the command.
 */
void TCPserver::handleUSER(User& user, std::vector<std::string> const& command) {
    if (!user.isRegistered()) {
        if (command.size() > 4) {
            if (command[1].size() > 0) {
                user.setUserName(command[1]);
                std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: username set to " << user.getUsername() << std::endl;
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " :username empty\r\n";
                sendReply(user, message);
                user.setAuthenticated(FALSE);
            }
            if (command[3].size() > 0)
                user.setHostname(command[3]);
            if (command[4].size() > 0) {
                std::string realname = "";
                for (std::string::size_type i(4); i < command.size(); i++) {
                    realname += command[i];
                    if (realname.find(":") != std::string::npos) {
                        realname.erase(realname.find(":", 0), 1);
                    }
                    if (i != command.size() - 1)
                        realname += " ";
                }
                user.setRealName(realname);
                std::cout << displayTimestamp() << "[INFO] Socket[" << user.getFD() << "]: realname set to " << user.getRealName() << std::endl;
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " :realname empty\r\n";
                sendReply(user, message);
                user.setAuthenticated(FALSE);
            }
        }
    } else {
        std::string message = std::string(ERR_ALREADYREGISTRED) + " :You may not reregister\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("USER");
}

/**
 * Registers a user to the server
 *
 * @param user The user to register.
 */
void TCPserver::registerUser(User& user) {
    User::command_iterator it_end = user.getCommandsEnd();
    /* wait for all commands needed for registration */
    if (user.getCommands().size() > 3) {
        User::command_iterator it = user.findCommand("PASS");
        /* if user did not send a PASS command, send error message */
        if (it == it_end) {
            handlePASS(user, "");
        } else {
            /* if user entered a password, check if it is valid */
            handlePASS(user, it->at(1));
        }
        std::vector<std::vector<std::string> > commands = user.getCommands();
        for (std::vector<std::vector<std::string> >::size_type i(0); i < commands.size(); i++) {
            if (commands[i].size() > 0) {
                if (commands[i][0] == "CAP") {
                    handleCAP(user, commands[i]);
                } else if (commands[i][0] == "NICK") {
                    handleNICK(user, commands[i][1]);
                } else if (commands[i][0] == "USER") {
                    handleUSER(user, commands[i]);
                }
            }
        }
        user.setRegistered(TRUE);
        if (user.isAuthenticated())
            sendWelcome(user);
    }
}

/**
 * Sends a welcome message to the user.
 *
 * @param user The user to send the message to.
 */
void TCPserver::sendWelcome(User& user) {
    std::string time = displayTimestamp();
    std::string message = std::string(RPL_WELCOME) + " " + user.getNickname() + "\r\n" + "Welcome to the Internet Relay Network, " + user.getNickname() + "[!" + user.getUsername() + "@" + user.getHostname() + "]\r\n";
    sendReply(user, message);
    message = std::string(RPL_YOURHOST) + " " + SERVER_NAME + " :Your host is " + SERVER_NAME + ", running version " + SERVER_VERSION + "\r\n";
    sendReply(user, message);
    message = std::string(RPL_CREATED) + " " + SERVER_NAME + " :This server was created at " + time + "\r\n";
    sendReply(user, message);
    message = std::string(RPL_MYINFO) + " " + SERVER_NAME + " " + SERVER_VERSION + " " + SERVER_USER_MODES + " " + SERVER_CHANNEL_MODES + "\r\n";
    sendReply(user, message);
    message = std::string(RPL_ISUPPORT) + " " + SERVER_NAME + " " + SERVER_ISUPPORT + "\r\n";
}

/**
 * WHOIS command:
 * https://modern.ircdocs.horse/#whois-message
 *
 * @param user a reference to the user object that is currently connected to the server
 * @param command a vector of strings, where each string is a word in the command.
 */
void TCPserver::handleWHOIS(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string nickname = "";
        /* if first arg is the server name and second arg is nickname */
        if (command[1] == SERVER_NAME && command.size() > 2)
            nickname = command[2];
        /* if first arg is nickname */
        else if (command[1] != SERVER_NAME)
            nickname = command[1];
        if (nickname.size() > 0) {
            /* check if nickname is valid */
            if (isNicknameValid(nickname)) {
                /* check if nickname is taken */
                if (isNicknameTaken(nickname, _users)) {
                    /* send WHOIS reply */
                    std::string message = std::string(RPL_WHOISUSER) + " " + user.getNickname() + " " + user.getNickname() + " " + user.getUsername() + " " + user.getHostname() + " * :" + user.getRealName() + "\r\n";
                    sendReply(user, message);
                    message = std::string(RPL_WHOISSERVER) + " " + user.getNickname() + " " + user.getNickname() + " " + SERVER_NAME + " :" + SERVER_VERSION + "\r\n";
                    sendReply(user, message);
                    message = std::string(RPL_ENDOFWHOIS) + " " + user.getNickname() + " " + user.getNickname() + " :End of WHOIS list\r\n";
                    sendReply(user, message);
                } else {
                    /* if nickname is not taken, send error message */
                    std::string message = std::string(ERR_NOSUCHNICK) + " " + nickname + " : No such nick/channel\r\n";
                    sendReply(user, message);
                }
            } else {
                /* if nickname is not valid, send error message */
                std::string message = std::string(ERR_ERRONEUSNICKNAME) + " " + nickname + " : Erroneous nickname\r\n";
                sendReply(user, message);
            }
        } else {
            /* if nickname is empty, send error message */
            std::string message = std::string(ERR_NONICKNAMEGIVEN) + " : No nickname given\r\n";
            sendReply(user, message);
        }
    } else {
        /* if command is empty, send error message */
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("WHOIS");
}

/**
 * PING command:
 * https://modern.ircdocs.horse/#ping-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent by the user.
 */
void TCPserver::handlePING(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string reply = "PONG " + command[1] + "\r\n";
        user.addReply(reply);
        sendReply(user, user.getReply());
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " : ERROR :No origin specified\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("PING");
}

/**
 * Handles the user part of the MODE command.
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command
 */
void TCPserver::handleUserMode(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2 && command[2].size() > 1) {
        std::string mode = command[2];
        if (mode[0] == '+') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_USER_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user.getNickname() + " :Unknown MODE flag\r\n";
                    sendReply(user, message);
                    return;
                } else {
                    user.setMode(mode[i], TRUE);
                }
            }
        } else if (mode[0] == '-') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_USER_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user.getNickname() + " :Unknown MODE flag\r\n";
                    sendReply(user, message);
                    return;
                } else {
                    user.setMode(mode[i], FALSE);
                }
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    std::string reply = std::string(RPL_UMODEIS) + " " + user.getNickname() + " " + user.getMode() + "\r\n";
    user.addReply(reply);
    sendReply(user, user.getReply());
}

/**
 * Handles the channel part of the MODE command.
 *
 * @param user The user who sent the command.
 * @param command the command that was sent to the server
 */
void TCPserver::handleChannelMode(User& user, std::vector<std::string> const& command) {
    std::string target = command[1];
    Channel& channel = getChannel(target);
    if (command.size() > 2) {
        std::string mode = command[2];
        if (mode[0] == '+') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_CHANNEL_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user.getNickname() + " :Unknown MODE flag\r\n";
                    sendReply(user, message);
                    return;
                }
                if (mode[i] == 'k') {
                    if (command.size() > 3) {
                        std::string key = command[3];
                        channel.setMode('k', TRUE);
                        channel.setKey(key);
                    }
                } else if (mode[i] == 'l') {
                    if (command.size() > 3) {
                        size_t limit = std::atoi(command[3].c_str());
                        channel.setMode('l', TRUE);
                        channel.setLimit(limit);
                    }
                } else if (mode[i] == 'b') {
                    if (command.size() > 3) {
                        std::string mask = command[3];
                        channel.setMode('b', TRUE);
                        channel.addBan(mask);
                    }
                } else if (mode[i] == 'v') {
                    if (command.size() > 3) {
                        // std::string nickname = command[3];
                        // if (isNicknameTaken(nickname, _users)) {
                        // }
                    }
                } else if (mode[i] == 'o') {
                    if (command.size() > 3) {
                        std::string nickname = command[3];
                        if (isNicknameTaken(nickname, _users)) {
                            user.setMode('o', TRUE);
                            channel.setMode('o', TRUE);
                            channel.addOperator(user);
                        } else {
                            std::string message = std::string(ERR_NOSUCHNICK) + " " + nickname + " :No such nick/channel\r\n";
                            sendReply(user, message);
                        }
                    }
                } else {
                    channel.setMode(mode[i], TRUE);
                }
            }
        } else if (mode[0] == '-') {
            for (std::string::size_type i(1); i < mode.size(); i++) {
                if (std::string(SERVER_CHANNEL_MODES).find(mode[i]) == std::string::npos) {
                    std::string message = std::string(ERR_UMODEUNKNOWNFLAG) + " " + user.getNickname() + " :Unknown MODE flag\r\n";
                    sendReply(user, message);
                    return;
                }
                if (mode[i] == 'k') {
                    channel.setMode('k', FALSE);
                    channel.setKey("");
                } else if (mode[i] == 'l') {
                    channel.setMode('l', FALSE);
                    channel.setLimit(0);
                } else if (mode[i] == 'b') {
                    if (command.size() > 3) {
                        std::string mask = command[3];
                        channel.setMode('b', FALSE);
                        channel.removeBan(mask);
                    }
                } else if (mode[i] == 'v') {
                    if (command.size() > 3) {
                        // std::string nickname = command[3];
                        // if (isNicknameTaken(nickname, _users)) {
                        // }
                    }
                } else if (mode[i] == 'o') {
                    if (command.size() > 3) {
                        std::string nickname = command[3];
                        if (isNicknameTaken(nickname, _users)) {
                            user.setMode('o', FALSE);
                            channel.setMode('o', FALSE);
                            channel.removeOperator(user);
                        } else {
                            std::string message = std::string(ERR_NOSUCHNICK) + " " + nickname + " :No such nick/channel\r\n";
                            sendReply(user, message);
                        }
                    }
                } else {
                    channel.setMode(mode[i], FALSE);
                }
            }
        }
    } else {
        std::string message = std::string(RPL_CHANNELMODEIS) + " " + channel.getName() + " " + channel.getMode() + "\r\n";
        sendReply(user, message);
    }
}

/**
 * MODE command:
 * https://modern.ircdocs.horse/#mode-message
 *
 * @param user The user who sent the command.
 * @param command a vector of strings, where each string is a word in the command.
 *
 */
void TCPserver::handleMODE(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = command[1];
        if (target.size() > 0 && target[0] == '#') {
            if (target.size() > 2) {
                if (isChannelNameValid(target)) {
                    handleChannelMode(user, command);
                } else {
                    std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + user.getNickname() + " " + target + " :No sucheeee channel\r\n";
                    sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user.getNickname() + " :Not enough parameters\r\n";
                sendReply(user, message);
            }
        } else {
            if (target.size() > 0) {
                if (isNicknameTaken(target, _users)) {
                    if (command.size() > 2) {
                        handleUserMode(user, command);
                    } else {
                        std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user.getNickname() + " :Not enough parameters\r\n";
                        sendReply(user, message);
                    }
                } else {
                    std::string message = std::string(ERR_NOSUCHNICK) + " " + user.getNickname() + " " + target + " :No such nick\r\n";
                    sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user.getNickname() + " :Not enough parameters\r\n";
                sendReply(user, message);
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " " + user.getNickname() + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("MODE");
}

/**
 * QUIT command:
 * https://modern.ircdocs.horse/#quit-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command
 */
void TCPserver::handleQUIT(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string reply = std::string(SERVER_NAME) + " QUIT " + user.getNickname() + "[!" + user.getUsername() + "@" + user.getHostname() + "] " + command[1] + "\r\n";
        user.deleteCommand("QUIT");
        user.addReply(reply);
        sendReply(user, user.getReply());
    }
}

/**
 * JOIN command:
 *
 * https://modern.ircdocs.horse/#join-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command.
 */
void TCPserver::handleJOIN(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (channel_name[0] == '#') {
                if (isChannelNameTaken(channel_name)) {
                    Channel& channelRef = getChannel(channel_name);
                    if (!channelRef.isUserInChannel(user)) {
                        if (!channelRef.isBanned(user)) {
                            channelRef.addUser(user);
                            user.addChannel(channelRef);
                            std::string reply = ":" + user.getFullname() + " JOIN :" + channel_name + "\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                            broadcastMessage(reply, channelRef.getUsers(), user);
                            reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channel_name + " :" + channelRef.getTopic() + "\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                            reply = std::string(RPL_NAMREPLY) + " " + user.getNickname() + " = " + channel_name + " : " + channelRef.getUsersNames() + "\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                            reply = std::string(RPL_ENDOFNAMES) + " " + user.getNickname() + " " + channel_name + " :End of /NAMES list\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                        } else {
                            std::string message = std::string(ERR_BANNEDFROMCHAN) + " " + user.getNickname() + " " + channel_name + " :You are banned from this channel\r\n";
                            sendReply(user, message);
                        }
                    } else {
                        std::string message = std::string(ERR_USERONCHANNEL) + " " + user.getNickname() + " " + channel_name + " :is already on channel\r\n";
                        sendReply(user, message);
                    }
                } else {
                    Channel newChannel(channel_name);
                    newChannel.addUser(user);
                    newChannel.addOperator(user);
                    user.setMode('o', TRUE);
                    std::string reply = std::string(RPL_UMODEIS) + " " + user.getNickname() + " " + user.getMode() + "\r\n";
                    user.addReply(reply);
                    sendReply(user, user.getReply());
                    user.addChannel(newChannel);
                    _channels.push_back(newChannel);
                    reply = ":" + user.getFullname() + " JOIN :" + channel_name + "\r\n";
                    user.addReply(reply);
                    sendReply(user, user.getReply());
                    reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channel_name + " :" + newChannel.getTopic() + "\r\n";
                    user.addReply(reply);
                    sendReply(user, user.getReply());
                    reply = std::string(RPL_NAMREPLY) + " " + user.getNickname() + " = " + channel_name + " : " + newChannel.getUsersNames() + "\r\n";
                    user.addReply(reply);
                    sendReply(user, user.getReply());
                    reply = std::string(RPL_ENDOFNAMES) + " " + user.getNickname() + " " + channel_name + " :End of /NAMES list\r\n";
                    user.addReply(reply);
                    sendReply(user, user.getReply());
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("JOIN");
}

/**
 * TOPIC command:
 *
 * @param user The user who sent the command.
 * @param command the command that was sent to the server
 */
void TCPserver::handleTOPIC(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (isChannelNameTaken(channel_name)) {
                Channel& channelRef = getChannel(channel_name);
                if (channelRef.isUserInChannel(user)) {
                    if (command.size() > 2) {
                        if (channelRef.isOperator(user)) {
                            std::string topic = "";
                            for (std::string::size_type i(2); i < command.size(); i++) {
                                topic += command[i] + " ";
                            }
                            channelRef.setTopic(topic);
                            std::string reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channel_name + " :" + channelRef.getTopic() + "\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                        } else {
                            std::string message = std::string(ERR_CHANOPRIVSNEEDED) + " " + channel_name + " :You're not channel operator\r\n";
                            sendReply(user, message);
                        }
                    } else {
                        if (channelRef.getTopic().size() > 0) {
                            std::string reply = std::string(RPL_TOPIC) + " " + user.getNickname() + " " + channel_name + " :" + channelRef.getTopic() + "\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                        } else {
                            std::string reply = std::string(RPL_NOTOPIC) + " " + user.getNickname() + " " + channel_name + " :No topic is set\r\n";
                            user.addReply(reply);
                            sendReply(user, user.getReply());
                        }
                    }
                } else {
                    std::string message = std::string(ERR_NOTONCHANNEL) + " " + user.getNickname() + " " + channel_name + " :You're not on that channel\r\n";
                    sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("TOPIC");
}

/**
 * PRIVMSG command:
 *
 * https://modern.ircdocs.horse/#privmsg-message
 *
 * @param user The user who sent the message
 * @param command the command that was sent by the user
 */
void TCPserver::handlePRIVMSG(User& user, std::vector<std::string> const& command) {
    if (command.size() > 2) {
        if (command[1][0] != '#') {
            privateChat(user, command);
            return;
        }
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (isChannelNameTaken(channel_name)) {
                Channel& channelRef = getChannel(channel_name);
                if (((channelRef.getMode().find('n') == std::string::npos) || (((channelRef.getMode().find('n') != std::string::npos) && channelRef.isUserInChannel(user))))
                && !channelRef.isBanned(user)) {
                    std::string message = "";
                    for (std::string::size_type i(2); i < command.size(); i++) {
                        message += command[i] + " ";
                    }
                    message = message.size() > MAX_MESSAGE_SIZE ? message.substr(0, MAX_MESSAGE_SIZE) : message;
                    std::string reply = ":" + user.getFullname() + " PRIVMSG " + channel_name + " " + message + "\r\n";
                    broadcastMessage(reply, channelRef.getUsers(), user);
                } else {
                    std::string message = std::string(ERR_CANNOTSENDTOCHAN) + " " + channel_name + " :Cannot send to channel\r\n";
                    sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("PRIVMSG");
}

/**
 * This function is used to send a private message to another user.
 * 
 * @param user The user who sent the command
 * @param command vector of strings, where each string is a word in the command
 */
void TCPserver::privateChat(User& user, std::vector<std::string> const& command) {
    std::map<int, User>::iterator it;
    for (it = _users.begin(); it != _users.end(); it++) {
        if (it->second.getNickname() == command[1]) {
            std::string message = "";
            for (std::string::size_type i(2); i < command.size(); i++) {
                message += command[i] + " ";
            }
            message = message.size() > MAX_MESSAGE_SIZE ? message.substr(0, MAX_MESSAGE_SIZE) : message;
            std::string reply = ":" + user.getFullname() + " PRIVMSG " + it->second.getNickname() + " " + message + "\r\n";
            sendReply(it->second, reply);
            user.deleteCommand("PRIVMSG");
            return;
        }
    }
    std::string message = std::string(ERR_NOSUCHNICK) + " " + command[1] + " : No such nick/channel\r\n";
    sendReply(user, message);
    user.deleteCommand("PRIVMSG");
}

/**
 * PART command:
 *
 * https://modern.ircdocs.horse/#part-message
 *
 * @param user The user who sent the command
 * @param command a vector of strings, where each string is a word in the command.
 */
void TCPserver::handlePART(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string channel_name = command[1];
        if (channel_name.size() > 0) {
            if (isChannelNameTaken(channel_name)) {
                Channel& channelRef = getChannel(channel_name);
                if (channelRef.isUserInChannel(user)) {
                    std::string reply = ":" + user.getFullname() + " PART " + channel_name;
                    if (command.size() > 2) {
                        std::string message = "";
                        for (std::string::size_type i(2); i < command.size(); i++) {
                            if (i == 2)
                                message += command[i][0] == ':' ? command[i].substr(1, command[i].size()) + " " : command[i] + " ";
                            else if (i == command.size() - 1)
                                message += command[i];
                            else
                                message += command[i] + " ";
                        }
                        reply += " :" + message + "\r\n";
                    } else {
                        reply += "\r\n";
                    }
                    sendReply(user, reply);
                    broadcastMessage(reply, channelRef.getUsers(), user);
                    channelRef.removeUser(user);
                    if (channelRef.getUsers().size() == 0) {
                        removeChannel(channel_name);
                    }
                } else {
                    std::string message = std::string(ERR_NOTONCHANNEL) + " " + user.getNickname() + " " + channel_name + " :You're not on that channel\r\n";
                    sendReply(user, message);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + channel_name + " :No such channel\r\n";
                sendReply(user, message);
            }
        } else {
            std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
            sendReply(user, message);
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("PART");
}

void TCPserver::handleWHO(User& user, std::vector<std::string> const& command) {
    if (command.size() > 1) {
        std::string target = command[1];
        if (target.size() > 0 && target[0] == '#') {
            if (isChannelNameTaken(target)) {
                Channel& channelRef = getChannel(target);
                std::map<int, User> users = channelRef.getUsers();
                for (std::map<int, User>::iterator it = users.begin(); it != users.end(); it++) {
                    if (user.getMode().find('i') == std::string::npos) {
                        std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_WHOREPLY + " " + user.getNickname() + " " + channelRef.getName() + " ~" + it->second.getUsername() + " " + it->second.getHostname() + " " + SERVER_NAME + " " + it->second.getNickname() + " H :0 " + it->second.getRealName() + "\r\n";
                        sendReply(user, reply);
                    }
                }
                std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_ENDOFWHO + " " + user.getNickname() + " " + target + " :End of /WHO list\r\n";
                sendReply(user, reply);
            } else {
                std::string message = std::string(ERR_NOSUCHCHANNEL) + " " + target + " :No such channel\r\n";
                sendReply(user, message);
            }
        } else {
            if (isNicknameTaken(target, _users)) {
                if (user.getMode().find('i') != std::string::npos) {
                    std::string message = std::string(ERR_USERSDONTMATCH) + " : Cannot send to a user who is invisible\r\n";
                    sendReply(user, message);
                } else {

                    std::string reply = ":" + std::string(SERVER_NAME) + " " + RPL_WHOREPLY + " " + user.getNickname() + " " + SERVER_NAME + " ~" + user.getUsername() + " " + user.getHostname() + " " + SERVER_NAME + " " + user.getNickname() + " H :0 " + user.getRealName() + "\r\n";
                    sendReply(user, reply);
                    std::string reply2 = ":" + std::string(SERVER_NAME) + " " + RPL_ENDOFWHO + " " + user.getNickname() + " " + target + " :End of /WHO list\r\n";
                    sendReply(user, reply2);
                }
            } else {
                std::string message = std::string(ERR_NOSUCHNICK) + " " + target + " :No such nick\r\n";
                sendReply(user, message);
            }
        }
    } else {
        std::string message = std::string(ERR_NEEDMOREPARAMS) + " :Not enough parameters\r\n";
        sendReply(user, message);
    }
    user.deleteCommand("WHO");
}

/**
 * MOTD command:
 *
 * https://modern.ircdocs.horse/#motd-message
 *
 * @param user The user who sent the command.
 * @param command The command that was sent by the user.
 */
void TCPserver::handleMOTD(User& user) {
    std::string message = std::string(RPL_MOTDSTART) + " :- " + SERVER_NAME + " Message of the day - \r\n";
    sendReply(user, message);
    std::ifstream file("motd/motd.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            message = std::string(RPL_MOTD) + " :- " + line + "\r\n";
            sendReply(user, message);
        }
        file.close();
    }
    message = std::string(RPL_ENDOFMOTD) + " : End of MOTD command\r\n";
    sendReply(user, message);
    user.deleteCommand("MOTD");
    user.deleteCommand("motd");
}

void TCPserver::handleLUSERS(User& user) {
    int invisible_users(0);
    for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++) {
        if (it->second.getMode().find('i') != std::string::npos) {
            invisible_users++;
        }
        std::string message = std::string(RPL_LUSERCLIENT) + " : There are " + toString(_users.size()) + " users and " + toString(invisible_users) + " invisible on 1 server\r\n";
        sendReply(user, message);
        // message = std::string(RPL_LUSEROP) + " 0 :operator(s) online\r\n";
        // sendReply(user, message);
        // message = std::string(RPL_LUSERUNKNOWN) + " 0 :unknown connection(s)\r\n";
        // sendReply(user, message);
        // message = std::string(RPL_LUSERCHANNELS) + toString(_channels.size()) + " 0 :channels formed\r\n";
        // sendReply(user, message);
        // message = std::string(RPL_LUSERME) + " : I have " + toString(_users.size()) + " clients and 0 servers\r\n";
        // sendReply(user, message);
    }
}

/**
 * Handles the commands sent by the client.
 *
 * @param user The user object that is connected to the client.
 */
void TCPserver::handleClientCommands(User& user) {
    std::vector<std::vector<std::string> > commands = user.getCommands();
    for (std::vector<std::vector<std::string> >::size_type i(0); i < commands.size(); i++) {
        if (commands[i].size() > 0) {
            if (commands[i][0] == "WHOIS") {
                handleWHOIS(user, commands[i]);
            } else if (commands[i][0] == "PING") {
                handlePING(user, commands[i]);
            } else if (commands[i][0] == "MODE") {
                handleMODE(user, commands[i]);
            } else if (commands[i][0] == "QUIT") {
                handleQUIT(user, commands[i]);
            } else if (commands[i][0] == "JOIN") {
                handleJOIN(user, commands[i]);
            } else if (commands[i][0] == "TOPIC") {
                handleTOPIC(user, commands[i]);
            } else if (commands[i][0] == "PRIVMSG") {
                handlePRIVMSG(user, commands[i]);
            } else if (commands[i][0] == "PART") {
                handlePART(user, commands[i]);
            } else if (commands[i][0] == "WHO") {
                handleWHO(user, commands[i]);
            } else if (commands[i][0] == "MOTD" || commands[i][0] == "motd") {
                handleMOTD(user);
            } else if (commands[i][0] == "LUSERS" || commands[i][0] == "lusers") {
                handleLUSERS(user);
            } else if (commands[i][0] == "NICK" && user.isRegistered()) {
                changeNICK(user, commands[i][1]);
            }
        }
    }
}

/**
 * Deletes a user from the server and prints infos to the console.
 *
 * @param i The index of the user to be deleted.
 */
void TCPserver::deleteUser(int const& i) {
    std::cout << displayTimestamp() << "[INFO] Connection closed on socket: [" << _pfds[i].fd << "]" << std::endl;
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++) {
        it->removeUser(_users[_pfds[i].fd]);
    }
    close(_pfds[i].fd);
    _pfds.erase(_pfds.begin() + i);
    _users.erase(_pfds[i].fd);
    std::cout << displayTimestamp() << "[INFO] Number of users connected: [" << _users.size() << "]" << std::endl;
}

/**
 * Sends a reply to a user and prints infos on the server's console
 *
 * @param user The user to send the reply to.
 * @param reply The message to send to the user.
 */
void TCPserver::sendReply(User& user, std::string const& reply) {
    std::string::size_type size(0);
    int bytesent(0);
    std::cout << displayTimestamp() << "[SENDING] Socket[" << user.getFD() << "]: " << reply;
    while (size < reply.size()) {
        if ((bytesent = send(user.getFD(), reply.c_str() + size, reply.size() - size, 0)) < 0)
            perror("send failed");
        size += bytesent;
    }
}

/**
 * Send the reply to all fd in the channel.
 *
 * @param reply The message to be sent to all users except the sender
 * @param users a map of all the users connected to the server
 * @param user The user who sent the message
 */
void TCPserver::broadcastMessage(std::string const& reply, std::map<int, User> users, User& user) {
    for (std::map<int, User>::iterator it = users.begin(); it != users.end(); it++) {
        if (it->second.getNickname() != user.getNickname()) {
            it->second.addReply(reply);
            sendReply(it->second, it->second.getReply());
        }
    }
}

/**
 * Remove a channel from the server.
 *
 * @param channelName The name of the channel to remove.
 */
void TCPserver::removeChannel(std::string const& channelName) {
    std::cout << displayTimestamp() << "[INFO] Removing channel: [" << channelName << "]" << std::endl;
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); it++) {
        if (it->getName() == channelName) {
            _channels.erase(it);
            break;
        }
    }
}
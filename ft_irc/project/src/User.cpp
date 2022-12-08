#include "User.hpp"

User::User()
    : _fd(-1), _nickname(""), _username(""), _realname(""), _hostname(""), _mode(""), _authenticated(TRUE), _registered(FALSE) { }

User::User(int const& fd)
    : _fd(fd), _nickname(""), _username(""), _realname(""), _hostname(""), _mode(""), _authenticated(TRUE), _registered(FALSE) { }

User::~User() {
    _fd = -1;
    _commands.clear();
    _replies.clear();
}

void User::addCommand(std::string const& command) {
    std::vector<std::string> tmp;
    std::string tmp2;
    std::stringstream ss(command);
    while (ss >> tmp2) {
        tmp.push_back(tmp2);
    }
    _commands.push_back(tmp);
}

User::command_iterator User::findCommand(std::string const& command) {
    for (command_iterator it = _commands.begin(); it != _commands.end(); ++it) {
        if ((*it)[0] == command) {
            return it;
        }
    }
    return _commands.end();
}

void User::deleteCommand(std::string const& command) {
    for (std::vector<std::vector<std::string> >::iterator it = _commands.begin(); it != _commands.end(); ++it) {
        if ((*it)[0] == command) {
            _commands.erase(it);
            break;
        }
    }
}

void User::printCommands() const {
    for (std::vector<std::vector<std::string> >::size_type i(0); i < _commands.size(); i++) {
        for (std::vector<std::string>::size_type j(0); j < _commands[i].size(); j++) {
            std::cout << displayTimestamp() << "[DEBUG] User[" << _fd << "] command[" << i << "][" << j << "]: " << _commands[i][j] << std::endl;
        }
    }
}

void User::setMode(char const& mode, int const& add) {
    if (add) {
        if (_mode.find(mode) == std::string::npos)
            _mode += mode;
    } else {
        if (_mode.find(mode) != std::string::npos)
            _mode.erase(_mode.find(mode), 1);
    }
}
#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#pragma once

#include "Channel.hpp"
#include "TCPsocket.hpp"
#include "User.hpp"
#include "include.hpp"
#include "utils.hpp"

class Channel;
class User;

class TCPserver {
public:
    TCPserver(int const& port, std::string const& password);
    ~TCPserver();

    /* core */
    void runServer();

    /* Users */
    void sendReply(User& user, std::string const& reply);
    void deleteUser(int const& i);

    /* Registration */
    void registerUser(User& user);
    void handleCAP(User& user, std::vector<std::string> const& command);
    void handlePASS(User& user, std::string const& password);
    void handleNICK(User& user, std::string const& command);
    void handleUSER(User& user, std::vector<std::string> const& command);
    void sendWelcome(User& user);

    /* Client commands */
    void handleClientCommands(User& user);
    void handleWHOIS(User& user, std::vector<std::string> const& command);
    void handlePING(User& user, std::vector<std::string> const& command);
    void handleQUIT(User& user, std::vector<std::string> const& command);
    void handleMODE(User& user, std::vector<std::string> const& command);
    void handleUserMode(User& user, std::vector<std::string> const& command);
    void handleChannelMode(User& user, std::vector<std::string> const& command);
    void handleJOIN(User& user, std::vector<std::string> const& command);
    void handleTOPIC(User& user, std::vector<std::string> const& command);
    void handlePRIVMSG(User& user, std::vector<std::string> const& command);
    void handlePART(User& user, std::vector<std::string> const& command);
    void handleWHO(User& user, std::vector<std::string> const& command);
    void privateChat(User& user, std::vector<std::string> const& command);
    void changeNICK(User &user, std::string const &nickname);

    void handleMOTD(User& user);
    void handleLUSERS(User& user);

    /* Getters */
    Channel& getChannel(std::string const& name);
    User& getUser(int const& user_fd);

    /* Utils */
    bool isChannelNameValid(std::string const& channelName);
    bool isChannelNameTaken(std::string const& channelName);

    /* Methods */
    void broadcastMessage(std::string const& reply, std::map<int, User> users, User& user);
    void removeChannel(std::string const& channelName);

private:
    TCPsocket _master_socket;
    std::vector<pollfd> _pfds;
    std::string _password;
    int _port;
    char _buffer[BUFFER_SIZE];
    std::map<int, User> _users;
    std::vector<Channel> _channels;
};

#endif // TCPSERVER_HPP
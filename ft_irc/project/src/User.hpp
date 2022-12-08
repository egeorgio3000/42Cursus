#ifndef USER_HPP
#define USER_HPP

#pragma once

#include "include.hpp"
#include "Channel.hpp"

class Channel;

class User {
public:
    User();
    User(int const& fd);
    ~User();

    /* typedef */
    typedef std::vector<std::vector<std::string> >::iterator command_iterator;

    /* _commands */
    void addCommand(std::string const& command);
    void deleteCommand(std::string const& command);
    command_iterator findCommand(std::string const& command);
    void printCommands() const;

    /* _replies */
    void addReply(std::string const& reply) { _replies.push_back(reply); }

    /* Getters */
    int getFD() const { return _fd; }
    std::string getNickname() const { return _nickname; }
    std::string getUsername() const { return _username; }
    std::string getRealName() const { return _realname; }
    std::string getHostname() const { return _hostname; }
    std::string getMode() const { return _mode; }
    std::string getFullname() const { return _nickname + "!~" + _username + "@" + _hostname; }
    std::vector<std::vector<std::string> > getCommands() const { return _commands; }
    int isAuthenticated() const { return _authenticated; }
    int isRegistered() const { return _registered; }
    std::string getReply() const { return _replies.back(); }
    command_iterator getCommandsEnd() { return _commands.end(); }
    command_iterator getCommandsBegin() { return _commands.begin(); }

    /* Setters */
    void setFD(int const& fd) { _fd = fd; }
    void setNickname(std::string const& nickname) { _nickname = nickname; }
    void setUserName(std::string const& username) { _username = username; }
    void setRealName(std::string const& realname) { _realname = realname; }
    void setHostname(std::string const& hostname) { _hostname = hostname; }
    void setMode(char const& mode, int const& add);
    void addChannel(Channel& channel) { _channels.push_back(channel); }
    void setAuthenticated(int const& authenticated) { _authenticated = authenticated; }
    void setRegistered(int const& registration) { _registered = registration; }

private:
    int _fd;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    std::string _hostname;
    std::string _mode;
    std::vector<Channel> _channels;
    int _authenticated;
    int _registered;
    std::vector<std::vector<std::string> > _commands;
    std::vector<std::string> _replies;
};

#endif // USER_HPP
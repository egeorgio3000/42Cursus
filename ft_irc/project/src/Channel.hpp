#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#pragma once

#include "TCPserver.hpp"
#include "User.hpp"
#include "include.hpp"

class User;

class Channel {
public:
    Channel();
    Channel(std::string const& name);
    ~Channel();

    /* Setters */
    void setName(std::string const& name) { _name = name; }
    void setTopic(std::string const& topic) { _topic = topic; }
    void setMode(char const& mode, int const& add);
    void setKey(std::string const& key) { _key = key; }
    void setLimit(int const& limit) { _limit = limit; }
    void setCreationTime(time_t const& creation_time) { _creationTime = creation_time; }
    void addOperator(User const& user);
    void removeOperator(User const& user);
    void addBan(std::string const& ban) { _bans.push_back(ban); }
    void removeBan(std::string const& ban) { _bans.erase(std::find(_bans.begin(), _bans.end(), ban)); }

    /* Getters */
    std::string getName() const { return _name; }
    std::string getTopic() const { return _topic; }
    std::string getMode() const { return _mode; }
    std::map<int, User> getUsers() const { return _users; }
    std::string getKeys() const { return _key; }
    size_t getLimit() const { return _limit; }
    std::string getUsersNames() const;
    std::vector<std::string> getOperators() const { return _operators; }
    std::vector<std::string> getBans() const { return _bans; }

    /* Users */
    void addUser(User const& user);
    void removeUser(User const& user);
    void sendMessage(std::string const& message, User const& user);
    bool isOperator(User const& user) const;
    bool isBanned(User const& user) const;
    bool isUserInChannel(User const& user) const;

private:
    std::string _name;
    std::string _topic;
    std::string _mode;
    std::string _key;
    size_t _limit;
    time_t _creationTime;
    std::map<int, User> _users;
    std::vector<std::string> _operators;
    std::vector<std::string> _bans;
};

#endif // CHANNEL_HPP
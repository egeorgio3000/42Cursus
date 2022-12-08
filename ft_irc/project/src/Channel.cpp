#include "Channel.hpp"

Channel::Channel() { }

Channel::Channel(std::string const& name)
    : _name(name), _mode(SERVER_CHANNEL_MODES), _limit(0), _creationTime(time(NULL)) { }

Channel::~Channel() { }

/* Getters */
std::string Channel::getUsersNames() const {
    std::string users_names;
    for (std::map<int, User>::const_iterator it = _users.begin(); it != _users.end(); ++it) {
        users_names += it->second.getNickname() + " ";
    }
    return users_names;
}

/* Setters */
void Channel::setMode(char const& mode, int const& add) {
    if (add) {
        if (_mode.find(mode) == std::string::npos)
            _mode += mode;
    } else {
        if (_mode.find(mode) != std::string::npos)
            _mode.erase(_mode.find(mode), 1);
    }
}

void Channel::addOperator(User const& user) {
    std::cout << displayTimestamp() << "[INFO] Adding operator " << user.getNickname() << " to channel " << _name << std::endl;
    _operators.push_back(user.getFullname());
}
void Channel::removeOperator(User const& user) {
    std::cout << displayTimestamp() << "[INFO] Removing operator " << user.getNickname() << " from channel " << _name << std::endl;
    _operators.erase(std::find(_operators.begin(), _operators.end(), user.getFullname()));
}

/* Users */
void Channel::addUser(User const& user) { _users.insert(std::pair<int, User>(user.getFD(), user)); }
void Channel::removeUser(User const& user) { _users.erase(user.getFD()); }
bool Channel::isOperator(User const& user) const { return std::find(_operators.begin(), _operators.end(), user.getFullname()) != _operators.end(); }
bool Channel::isUserInChannel(User const& user) const { return _users.find(user.getFD()) != _users.end(); }
bool Channel::isBanned(User const& user) const { return std::find(_bans.begin(), _bans.end(), user.getFullname()) != _bans.end(); }
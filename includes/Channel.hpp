#pragma once

#include <vector>
#include "User.hpp"

class Channel{
    public:
        Channel(const IrcServer &irc_server, size_t operator_id, const std::string &channel_name) :
            channelName_(channel_name), operator_(operator), users_(operator), channelId_(irc_server.getNewChannelId());
        ~Channel() {};
        int     addUser(const IrcServer &irc_server, size_t user_id) { return 0 };
        int     removeUser(const IrcServer &irc_server, size_t user_id) { return 0 };
    private:
        std::string                     channelName_;
        const User                      &operator_;
        std::vector<size_t>             users_;
        size_t                          channelId_;
};
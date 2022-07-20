#pragma once

#include <vector>
#include "User.hpp"

class IrcServer;

class Channel{
    public:
        Channel(std::size_t channel_id, const User &channel_operator, const std::string &channel_name) :
            channelName_(channel_name), channelOperator_(channel_operator), channelId_(channel_id) {
                users_.push_back(channel_operator);
            };
        ~Channel() {};
        int     addUser(const User &channel_member);
        int     removeUser(const User &channel_member);
    private:
        std::string                         channelName_;
        const User                          &channelOperator_;
        std::vector<User>                   users_;
        std::size_t                         channelId_;
};
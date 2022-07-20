#pragma once

#include <iostream>
#include "ConfigValues.hpp"
#include "FD.hpp"
#include "Channel.hpp"
#include "User.hpp"
#include "MessageServer.hpp"

#define BUF_SIZE 512 // messages SHALL NOT exceed 512 characters in length

class IrcServer {
	private:
		std::vector<Channel>		channels_;
		std::vector<User>			users_;
		std::size_t					availableUserId_;
		std::size_t					availableChannelId_;
		MessageServer				msgServer_;
	public:
		//IrcServer(const char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket);
		IrcServer(const ConfigValues& config_values) : msgServer_(config_values) {};
		~IrcServer(void) {};

		// add_channel_to_array_of_channels(Channel *channel);
		// add_chat_to_array_of_chats(PrivateChat *chat);
		std::size_t		getAvailableUserId(void);
		std::size_t		getAvailableChannelId(void);
};
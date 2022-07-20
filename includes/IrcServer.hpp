#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include "ConfigValues.hpp"
#include "FD.hpp"
#include "Channel.hpp"
#include "User.hpp"

#define BUF_SIZE 512 // messages SHALL NOT exceed 512 characters in length

class IrcServer {
	private:
		const char    				*hostname_;
		unsigned short     			port_;
		int							listen_socket_;
		std::vector<Channel>		channels_;
		std::vector<User>			users_;
		std::size_t					availableUserId_;
		std::size_t					availableChannelId_;
	public:
		std::size_t    				fd_capacity_;
		FD							*fds_array_;

		//IrcServer(const char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket);
		IrcServer(const ConfigValues& config_values);
		~IrcServer(void);

		void			print_server_values(void);
		// add_channel_to_array_of_channels(Channel *channel);
		// add_chat_to_array_of_chats(PrivateChat *chat);
		std::size_t		getAvailableUserId(void);
		std::size_t		getAvailableChannelId(void);
};
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

#define BUF_SIZE 512 // messages SHALL NOT exceed 512 characters in length

class IrcServer {
	private:
		const char    		*hostname_;
		unsigned short     	port_;
		int					listen_socket_;
		// Channel 			channels[3];
		// PrivateChat 		chats[3];
	public:
		unsigned long long int    	fd_capacity_;
		FD							*fds_array_;
		//IrcServer(const char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket);
		IrcServer(const ConfigValues& config_values);
		~IrcServer(void);
		void	print_server_values(void);
		// add_channel_to_array_of_channels(Channel *channel);
		// add_chat_to_array_of_chats(PrivateChat *chat);

};
#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <vector>

#define BUF_SIZE 512 // messages SHALL NOT exceed 512 characters in length

#define PROGRAM_NAME "ircserv"
#define USAGE_NOT_PRINTED 0
#define USAGE_PRINTED 1
#define ERRORS_NUM 10
enum  error_ircserv {
	CONFIG_NOFILE = 0,
	CONFIG_DOUPLICATE_FILE,
	CONFIG_CANNOT_OPEN,
	CONFIG_WRONG_FORMAT,
	CONFIG_NOKEY,
	CONFIG_VALUE_INVALID,
	CONFIG_KEY_EMPTY,
	CONFIG_VALUE_EMPTY,
	SERVER_NO_HOSTIP,
	SERVER_CANNOT_SOCKET,
};

class ConfigValues {
	private:
		struct			config_value_ {
			std::string		keys_;
			std::string		regexp_;
			std::string		values_;
		};
	public:
		std::vector<struct config_value_>	config_values_;
		ConfigValues (void);
		~ConfigValues(void);
		const std::string& 	get_value_from_array(const char *key) const;
		void			save_value_by_key(const std::string& key, const std::string& value);
		bool			check_value_by_regexp(const size_t index, const std::string& value) const;
};

class FD {
	public:
		FD(void) { };
		~FD(void) { };
};

class MainServer {
	private:
		const char    		*hostname_;
		unsigned short     	port_;
		int					listen_socket_;
		// Channel 			channels[3];
		// PrivateChat 		chats[3];
	public:
		intmax_t    		fd_capacity_;
		FD					*fds_array_;
		//MainServer(const char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket);
		MainServer(const ConfigValues& config_values);
		~MainServer(void);
		void	print_server_values(void);
		// add_channel_to_array_of_channels(Channel *channel);
		// add_chat_to_array_of_chats(PrivateChat *chat);
};


class User {
	private:
		// int			port;
		// int			socket_fd;
	public:
		// char	buf_read[BUF_SIZE + 1];
  		// char	buf_write[BUF_SIZE + 1];
		User(int port, int socket_fd);
		~User(void);
		// read_from_tcp();
		// write_to_tcp();
};

class Channel {
	private:
		// int		id;
		// char    name[51];
		// fd_set  fds_read;
		// fd_set  fds_write;
	public:
		// Channel(void) {}
		// Channel(char *name);
		// ~Channel(void);
		// add_client_to_channel(int socket_fd);
};

class PrivateChat {
	private:
		// fd_set  *fds_read;
		// fd_set  *fds_write;
	public:
		// PrivateChat(void);
		// ~PrivateChat(void);
		// add_client_to_array_of_chats(int first_socket_fd, int second_socket_fd);
};


int			errors_management(error_ircserv ertype, std::string argument, bool usage_needed);
void		irc_usage(void);
void    	create_server(MainServer *irc_server, ConfigValues& config_values);
void		check_config_file(int argc, char *argv[], ConfigValues& config_values);

#endif
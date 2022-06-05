#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include <iostream>
#include <cstring>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <netinet/in.h>

#define BUF_SIZE 512 // messages SHALL NOT exceed 512 characters in length
extern const int		backlog_to_listen;

#define PROGRAM_NAME "ircserv"
#define ERRORS_NUM 9
enum  error_ircserv {
	CONFIG_NOFILE = 0,
	CONFIG_DOUPLICATE_FILE,
	CONFIG_CANNOT_OPEN,
	CONFIG_WRONG_FORMAT,
	CONFIG_NOKEY,
	CONFIG_DOUBLICATE_KEY,
	CONFIG_VALUE_INVALID,
	CONFIG_KEY_EMPTY,
	CONFIG_VALUE_EMPTY,
};

#define	CONFIG_VALUES_NB	2
class ConfigValues {
	public:
		size_t			config_values_nb;
		std::string		keys[CONFIG_VALUES_NB];
		std::string		regexp[CONFIG_VALUES_NB];
		std::string		values[CONFIG_VALUES_NB];
		ConfigValues (void);
		~ConfigValues(void);
		std::string 	get_value_from_array(const char *key);
		bool			check_value_by_regexp(size_t index, std::string& value);
		void			save_value_by_key(std::string key, std::string value);
};

class User {
	private:
		char		*hostname;
		int			port;
		int			socket_fd;
	public:
		char	buf_read[BUF_SIZE + 1];
  		char	buf_write[BUF_SIZE + 1];
		User(char *hostname, int port, int socket_fd);
		~User(void);
		// read_from_tcp();
		// write_to_tcp();
};

class Channel {
	private:
		int		id;
		char    name[51];
		fd_set  fds_read;
		fd_set  fds_write;
	public:
		Channel(void) {}
		Channel(char *name);
		~Channel(void);
		// add_client_to_channel(int socket_fd);
};

class PrivateChat {
	private:
		fd_set  *fds_read;
		fd_set  *fds_write;
	public:
		PrivateChat(void);
		~PrivateChat(void);
		// add_client_to_array_of_chats(int first_socket_fd, int second_socket_fd);
};

class Server {
	private:
		char    			*hostname;
		unsigned short     	port;
		int					listen_socket;
		Channel 			channels[3];
		PrivateChat 		chats[3];
	public:
		intmax_t    fd_capacity;
		Server(void);
		Server(char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket);
		~Server(void);
		// add_channel_to_array_of_channels(Channel *channel);
		// add_chat_to_array_of_chats(PrivateChat *chat);
};

int			errors_management(error_ircserv ertype, std::string argument, bool usage_needed);
int			irc_usage(void);
int			check_config_file(int argc, char *argv[], ConfigValues& config_values);

#endif
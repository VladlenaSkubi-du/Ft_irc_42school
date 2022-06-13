#include "ircserv.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <fcntl.h>

#define	DEFAULT_SOFT_LIMIT 8
#define DEFAULT_HARD_LIMIT 16

static void	listen_server_socket(int& server_socket) {
	const int	backlog_to_listen = 10;
	if (listen(server_socket, backlog_to_listen))
		exit(errors_management(SERVER_CANNOT_SOCKET, "", USAGE_NOT_PRINTED));
}

static void	make_server_socket_tcp(int& server_socket, struct sockaddr_in&  serv_addr) {
	if (bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
		exit(errors_management(SERVER_CANNOT_SOCKET, "", USAGE_NOT_PRINTED));
}

static void	define_tcp_parameters(struct sockaddr_in& serv_addr, ConfigValues& config_values) {
	memset(&serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	uint16_t port = static_cast<uint16_t>(atoi(config_values.get_value_from_array("PORT").c_str()));
	serv_addr.sin_port = htons(port);
	inet_aton(config_values.get_value_from_array("HOSTNAME").c_str(), &serv_addr.sin_addr);
}

static int	create_server_socket_with_type_tcp(void) {
	int  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1)
		exit(errors_management(SERVER_CANNOT_SOCKET, "", USAGE_NOT_PRINTED));
	return(server_socket);
}

static void	get_system_limits_of_fd_number(struct rlimit& resource_limit) {
	if (getrlimit(RLIMIT_NOFILE, &resource_limit)) {
		resource_limit.rlim_cur = DEFAULT_SOFT_LIMIT;
		resource_limit.rlim_max = DEFAULT_HARD_LIMIT;
	}
}

void    create_server(Server *irc_server, ConfigValues& config_values) {

	struct rlimit  resource_limit;
	get_system_limits_of_fd_number(resource_limit);
	int server_socket = create_server_socket_with_type_tcp();

	struct sockaddr_in  serv_addr;
	define_tcp_parameters(serv_addr, config_values);
	make_server_socket_tcp(server_socket, serv_addr);
	listen_server_socket(server_socket);

	irc_server = new Server(config_values.get_value_from_array("HOSTNAME").c_str(), ntohs(serv_addr.sin_port), 
		static_cast<intmax_t>(resource_limit.rlim_cur), server_socket);
	irc_server->print_server_values(); // TO delete
}
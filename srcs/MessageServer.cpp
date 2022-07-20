#include "MessageServer.hpp"
#include "debug.hpp"

namespace {
    const int     DEFAULT_SOFT_LIMIT = 8;
    const int     DEFAULT_HARD_LIMIT = 16;

    void	listen_server_socket(int& server_socket) {
	    const int	backlog_to_listen = 10;
	    if (listen(server_socket, backlog_to_listen))
	    	exit(errors_management(SERVER_CANT_SOCKET, "", USAGE_NOT_PRINTED));
    }

    void	make_server_socket_tcp(int& server_socket, struct sockaddr_in&  serv_addr) {
    	if (bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
    		exit(errors_management(SERVER_CANT_SOCKET, "", USAGE_NOT_PRINTED));
    }

    void	define_tcp_parameters(struct sockaddr_in& serv_addr, const ConfigValues& config_values) {
    	memset(&serv_addr, '\0', sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	uint16_t port = static_cast<uint16_t>(atoi(config_values.get_value_from_array("PORT").c_str()));
    	serv_addr.sin_port = htons(port);
    	hostent *hostname = gethostbyname(config_values.get_value_from_array("HOSTNAME").c_str());
    	if (!hostname)
    		exit(errors_management(SERVER_NO_HOSTIP, config_values.get_value_from_array("HOSTNAME"), USAGE_NOT_PRINTED));
    	inet_aton(hostname->h_name, &serv_addr.sin_addr);
    }

    int	create_server_socket_with_type_tcp(void) {
    	int  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    	if (server_socket == -1)
    		exit(errors_management(SERVER_CANT_SOCKET, "", USAGE_NOT_PRINTED));
    	return(server_socket);
    }

    void	get_system_limits_of_fd_number(struct rlimit& resource_limit) {
    	if (getrlimit(RLIMIT_NOFILE, &resource_limit)) {
    		resource_limit.rlim_cur = DEFAULT_SOFT_LIMIT;
    		resource_limit.rlim_max = DEFAULT_HARD_LIMIT;
    	}
    }
}

void    MessageServer::print_server_values(void) {
    std::cout << "IrcServer values:\n" <<
        "\tHost IP is " << hostname_ << std::endl <<
        "\tPort is " << port_ << std::endl <<
        "\tSystem allows " << fd_capacity_ << " number of fds" << std::endl <<
        "\tIrcServer listens to fd number " << listen_socket_ << std::endl;
}

MessageServer::MessageServer(const ConfigValues& config_values) {
    struct rlimit  resource_limit;
	get_system_limits_of_fd_number(resource_limit);
	int server_socket = create_server_socket_with_type_tcp();

	struct sockaddr_in  serv_addr;
	define_tcp_parameters(serv_addr, config_values);
	make_server_socket_tcp(server_socket, serv_addr);
	listen_server_socket(server_socket);

    hostname_ = config_values.get_value_from_array("HOSTNAME");
    port_ = ntohs(serv_addr.sin_port);
    fd_capacity_ = static_cast<std::size_t>(resource_limit.rlim_cur);
    listen_socket_ = server_socket;
    fds.resize(fd_capacity_);
	print_server_values();
}
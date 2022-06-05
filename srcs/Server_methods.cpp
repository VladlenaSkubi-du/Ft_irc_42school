#include "ircserv.hpp"

Server::Server(void) {}

Server::Server(const char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket) {
    this->hostname = hostname;
    this->port = port;
    this->fd_capacity = fd_capacity;
    this->listen_socket = listen_socket;
}

Server::~Server(void) {}

void    Server::print_server_values(void) {
    std::cout << "Server values:\n" <<
        "\tHostname is " << this->hostname << std::endl <<
        "\tPort is " << this->port << std::endl <<
        "\tSystem allows " << this->fd_capacity << " number of fds" << std::endl <<
        "\tServer listens to socket number " << this->listen_socket << std::endl;
}

// Channel::Channel(char *name) {
// 	strncpy(this->name, name, 50);
// 	this->name[50] = '\0';
// }

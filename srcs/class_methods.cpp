#include "ircserv.hpp"

Server::Server(void) {}

Server::Server(char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket) {
    this->hostname = hostname;
    this->port = port;
    this->fd_capacity = fd_capacity;
    this->listen_socket = listen_socket;
}

unsigned short Server::get_server_port(void) {
	return this->port;
}

Channel::Channel(char *name) {
	strncpy(this->name, name, 50);
	this->name[50] = '\0';
}
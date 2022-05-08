#include "ircserv.hpp"

Server::Server(void) {}

Server::Server(char *hostname, unsigned short port, intmax_t fd_capacity, int listen_socket) {
    it->hostname = hostname;
    it->port = port;
    it->fd_capacity = fd_capacity;
    it->listen_socket = 
}
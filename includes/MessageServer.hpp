#pragma once

#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include "ConfigValues.hpp"
#include "FD.hpp"

class MessageServer {
    public:
        MessageServer(const ConfigValues& config_values);
        ~MessageServer() {};

        void            get_message();
        void            send_message();
        void			print_server_values(void);
    private:
        void                *read_func();
        void                *write_func();
        std::size_t    		fd_capacity_;
        std::vector<FD>     fds;
        std::string    		hostname_;
		unsigned short     	port_;
		int					listen_socket_;
};
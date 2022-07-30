#pragma once

#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <queue>
#include <string.h>
#include <cctype>
#include <cstdlib>


#define USAGE "./ircbot <port> <password>"
#define INVALID_PARAMETRS "Invalid parametrs:\nPort and password must be non-zero\nPort cannot be negative or zero"

class IRCBot{
    public:
        IRCBot(unsigned short int port, std::string password, std::string hostname = std::string("127.0.0.1"));
        void    run(void);
    private:
        void                        sendMessage(const std::string &message);
        void                        authentication();
        void                        splitBuff();
        void                        commandCompute();
        std::vector<std::string>    split(const std::string &str);

        int                     fd_;
        unsigned short int      port_;
        std::string             password_;
        std::string             hostname_;
        std::string             nickname_;
        std::string             readBuff_;
        std::queue<std::string> messages_;
};
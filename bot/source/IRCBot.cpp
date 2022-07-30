#include "IRCBot.hpp"
#include <errno.h>
IRCBot::IRCBot(unsigned short int port, std::string password, std::string hostname) :
        port_(port), password_(password), hostname_(hostname) {
    nickname_ = std::string("Ebot");
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(hostname.c_str());
    server_addr.sin_port = htons(port_);
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0)
        throw std::runtime_error("Can't create server socket!");
    if (connect(fd_, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        std::cout << strerror(errno) << "   " << server_addr.sin_addr.s_addr <<  std::endl;
        throw std::runtime_error("Can't connect to the server!");
    }
}

void IRCBot::sendMessage(const std::string &message) {
    std::cout << "Sending : [\033[0;32m " << message << " \033[0m]" << std::endl;

    std::string     forSend = message + "\r\n";
    send(fd_, forSend.c_str(), forSend.size(), 0);
}

void    IRCBot::authentication(){
    sendMessage("PASS " + password_);
    sendMessage("NICK " + nickname_);
    sendMessage("USER Ebotyara ignore_hostName ignore_serverName :Ebot_Jr.");
    // sendMessage("USER mikhail mikhail 127.0.0.1 :Mikhail");
}

void    IRCBot::splitBuff(){
    std::size_t start = 0, end = 0, newStringStart = 0;
    for (std::size_t i = 0; i < readBuff_.size(); ++i) {
        if (i < readBuff_.size() - 1 && readBuff_[i] == '\r' && readBuff_[i + 1] == '\n'){
            char buff[513];
            bzero(buff, 513);
            strncpy(buff, &readBuff_.c_str()[start], end - start);
            if (end - start > 0) {
                messages_.push(std::string(buff));
                std::cout << "New command recieve: [\033[0;32m " << buff << " \033[0m]" << std::endl;
            }
            i += 2;
            start = i;
            end = i;
            newStringStart = i;
        } else
            ++end;
    }
    readBuff_ = std::string(&readBuff_.c_str()[newStringStart]);

} 

void    IRCBot::run() {
    authentication();

    char buff[513];
    int len;
    while (true){
        while ( (len = recv(fd_, buff, 512, 0)) ){
            buff[len] = '\0';
            std::cout << buff << std::endl;
            readBuff_ += std::string(buff);
            splitBuff();
            if (messages_.size() > 0)
                commandCompute();
        }
    }
}

std::vector<std::string>       IRCBot::split(const std::string &str){
    std::size_t start = 0, end = 0;
    std::vector<std::string>    ans;
    for (std::size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ':' && start == i && start != 0) {
            char buff[513];
            bzero(buff, 513);
            strncpy(buff, &str.c_str()[start], str.size() - start);
            ans.push_back(std::string(buff));
            break;
        }
        else if (std::isspace(static_cast<unsigned char>(str[i]))) {
            if (start != i){
                char buff[513];
                bzero(buff, 513);
                strncpy(buff, &str.c_str()[start], end + 1 - start);
                ans.push_back(std::string(buff));
            }
            start = i + 1;
            end = i + 1;
        } else {
            ++end;
        }
    }
    if (start != end){
        char buff[513];
        bzero(buff, 513);
        strncpy(buff, &str.c_str()[start], end + 1 - start);
        ans.push_back(std::string(buff)); 
    }
    return ans;
}

void    IRCBot::commandCompute(){
    while (messages_.size()){
        std::string str = messages_.front();
        std::cout << str << std::endl;
        std::vector<std::string> message = split(str);
        for (size_t i = 0; i < message.size(); ++i)
            std :: cout << i << "  " << message[i] << std::endl;
        if (std::atoi(message[1].c_str()) != 0)
            std::cout << message[1].c_str() << std::endl;
        else
            std::cout << message[1].c_str() << std::endl;
        messages_.pop();
    }
}

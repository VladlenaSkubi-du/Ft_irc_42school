#pragma once

#include <string>

class User{
    public:
        User(std::string nickname, std::string name, std::string password, size_t index_io) : 
            nickname_(nickname), name_(name), paswword_(password), indexIoBuff_(index) {};
        ~User() {};

        void setNickname(const std::string &nickname) { nickname_(nickname) };
        void setName(const std::string &name) { name_(name) };
        void setPassword(const std::string &password) { password_(password) };

        const std::string &getNickname(void) { return nickname_; };
        const std::string &getName(void) { return name_; };
        const std::string &getPassword(void) { return password_; };
        size_t             getIndexIO(void) { return indexIoBuff_; };
        size_t             getId(void) { return id_; };
    private:
        std::string     nickname_;
        std::string     name_;
        std::string     password_;
        size_t          indexIoBuff_;
        size_t          id_;
};
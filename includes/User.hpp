#pragma once

#include <string>

class User{
    public:
        User(std::string nickname, std::string name, std::string password, std::size_t index_io, std::size_t id) : 
            nickname_(nickname), name_(name), password_(password), indexIoBuff_(index_io), id_(id) {};
        ~User() {};

        void setNickname(const std::string &nickname) { nickname_.assign(nickname); };
        void setName(const std::string &name) { name_.assign(name); };
        void setPassword(const std::string &password) { password_.assign(password); };

        const std::string       &getNickname(void) { return nickname_; };
        const std::string       &getName(void) { return name_; };
        const std::string       &getPassword(void) { return password_; };
        std::size_t             getIndexIO(void) { return indexIoBuff_; };
        std::size_t             getId(void) { return id_; };
    private:
        std::string             nickname_;
        std::string             name_;
        std::string             password_;
        std::size_t             indexIoBuff_;
        std::size_t             id_;
};
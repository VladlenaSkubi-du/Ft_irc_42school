#pragma once

#include <string>

enum FdType {
    NO_TYPE,
    SERVER,
    CLIENT
};

class FD {
	public:
        FD() { type_ = NO_TYPE; fd_ = -1; };
        FD(FdType type, int fd) : type_(type), fd_(fd) { };
		~FD() {};

        void            setType(const FdType type) { type_ = type; };
        void            setFd(const int fd) { fd_ = fd; };

        const FdType    getType(void) { return type_; };
        int             getFd(void) { return fd_; };
        std::string     &getReadBuff(void) { return readBuff_; };
        std::string     &getWriteBuff(void) { return writeBuff_; };

    private:
        FdType          type_;
        std::string     readBuff_;
        std::string     writeBuff_;
        int             fd_;
};
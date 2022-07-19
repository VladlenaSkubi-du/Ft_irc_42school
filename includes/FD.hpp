#pragma once

#include <string>

enum TypeFD {
    NO_TYPE,
    SERVER,
    CLIENT
};

class FD {
	public:
        FD() { type_ = NO_TYPE; };
		~FD() {};

        void            setType(const TypeFD type) { type_ = type;};

        const TypeFD    getType(void) { return type_;};
        std::string     &getReadBuff(void) { return readBuff_; };
        std::string     &getWriteBuff(void) { return writeBuff_; };
    private:
        TypeFD          type_;
        std::string     readBuff_;
        std::string     writeBuff_;
};
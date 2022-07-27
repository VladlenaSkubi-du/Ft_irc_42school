#pragma once

#include <iostream>

namespace specialCharacters {
    enum characters {
        NUL = 0x0,
        CR = 0xd,
        LF = 0xa,
    };
};

namespace IrcCommands {
    enum commands{
        PRIVMSG = 1,
        NOTICE,
        PASS,
        NICK,
        USER,
        PING,
        PONG,
        KILL,
        JOIN,
        PART,
        MODE,
        OPER,
        KICK,
        WHO,
        WHOIS,
        LIST,
        QUIT,
    };
}

class IrcParser {
    public:
        IrcParser();
        ~IrcParser();
        bool    check_user(char c);
        bool    check_special(char c);
        bool    check_number(char c);
        bool    check_letter(char c);
        bool    check_nonwhite(char c);
};

class IrcServer {
    private:
        std::string     password = "password";
        IrcParser       ircParser_;
    public:
        IrcServer(const std::string& password);
        ~IrcServer();
};

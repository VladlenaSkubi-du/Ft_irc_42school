#include "IRCServer.hpp"

IrcParser::IrcParser() {

};

IrcParser::~IrcParser() {

};

bool    IrcParser::check_special(char c) {
    if (c == '-' || c == '[' || c ==']' || 
        c == '\'' || c == '`' || c == '^' || 
        c == '{' || c == '}')
            return (true);
    return (false);
}

bool    IrcParser::check_number(char c) {
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

bool    IrcParser::check_letter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (true);
    return (false);
}

bool    IrcParser::check_nonwhite(char c) {
    if (c == ' ' || c == specialCharacters::characters::NUL ||
        c == specialCharacters::characters::CR ||
        c == specialCharacters::characters::LF)
            return (false);
    return (true);
}

bool    IrcParser::check_user(char c) {
    
}

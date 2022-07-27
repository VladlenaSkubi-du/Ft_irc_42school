#include "main.hpp"

static std::string add_nickname(int argc, char *argv_nick) {
    std::string nick;

    if (argc != 3) {
        printf("Default nickname: default\n");
        nick = "default";
    }
    else {
        nick = argv_nick;
    }
    return (nick);
}

static std::string irc_ping(std::string nick) {
    if (DEBUG_MODE) {
        std::cout << "Client asks: /PING " << nick << std::endl;
    }
    
    return ("done");
}

static void parse_commands(int argc, char *argv[]) {
    std::string client_command(argv[1]);
    std::map <std::string, int> mapping;

    mapping["/PRIVMSG"] = PRIVMSG;
    mapping["/privmsg"] = PRIVMSG;

    mapping["NOTICE"] = NOTICE;
    mapping["/notice"] = NOTICE;

    mapping["PASS"] = PASS;
    mapping["/pass"] = PASS;

    mapping["/NICK"] = NICK;
    mapping["/nick"] = NICK;

    mapping["/USER"] = USER;
    mapping["/user"] = USER;

    mapping["/PING"] = PING;
    mapping["/ping"] = PING;

    mapping["/PONG"] = PONG;
    mapping["/pong"] = PONG;

    mapping["/KILL"] = KILL;
    mapping["/kill"] = KILL;

    mapping["/JOIN"] = JOIN;
    mapping["/join"] = JOIN;

    mapping["/PART"] = PART;
    mapping["/part"] = PART;

    mapping["/MODE"] = MODE;
    mapping["/mode"] = MODE;

    mapping["/OPER"] = OPER;
    mapping["/oper"] = OPER;

    mapping["/KICK"] = KICK;
    mapping["/kick"] = KICK;

    mapping["/WHO"] = WHO;
    mapping["/who"] = WHO;

    mapping["/WHOIS"] = WHOIS;
    mapping["/whois"] = WHOIS;

    mapping["/LIST"] = LIST;
    mapping["/list"] = LIST;

    mapping["/QUIT"] = QUIT;
    mapping["/quit"] = QUIT;
    
    std::string reply;
    switch (mapping[client_command]) {
        case PING:
            reply = irc_ping(add_nickname(argc, argv[2])); 
            break;
        default:
            std::cout << "Command not found" << std::endl;
            break;
    }
    std::cout << "Server answers: " << reply << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter IRC client command\n");
        return (0);
    }
    parse_commands(argc, argv);
	// IrcServer irc_server(config_values);
	return (0);
}
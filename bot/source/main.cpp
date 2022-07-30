#include "IRCBot.hpp"

int main(int argc, char **argv){
    try {

        if (argc < 3) {
            throw std::runtime_error(USAGE);
        } else {
            std::string     portString(argv[1]);
            std::string     passwordString(argv[2]);
            int             checkPort;

            checkPort = std::atoi(portString.c_str());
            if (portString.empty() || passwordString.empty() || checkPort < 1){
                throw std::runtime_error(INVALID_PARAMETRS);
            } else {
                unsigned short int      port = std::atoi(portString.c_str());
                IRCBot  bot(port, passwordString);
                bot.run();
            }
        }
    } catch (std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
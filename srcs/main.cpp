#include "ircserv.hpp"

int main(int argc, char *argv[]) {
	ConfigValues config_values;
	check_config_file(argc, argv, config_values);
	Server *irc_server = NULL;
	create_server(irc_server, config_values);
	delete irc_server;
	return (0);
}

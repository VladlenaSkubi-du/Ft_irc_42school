#include "ircserv.hpp"

#define SERVER_WORKS 1
#define SERVER_TERMINATED -1

// static bool	server_state;

// static void terminate_server(int signal)
// {
// 	if (signal == SIGINT)
// 		server_state = SERVER_TERMINATED;
// }

int main(int argc, char *argv[]) {
	ConfigValues config_values;
	check_config_file(argc, argv, config_values);
	MainServer irc_server(config_values);

	// int	server_state = SERVER_WORKS;
	// signal(SIGINT, terminate_server);
	// while (server_state == SERVER_WORKS) {
	// 	accept_client(irc_server);
		
	// }
	// если получаем sigint, нужно сперва проверить, все ли мы полученное отправили клиентам, далее отправить SQUIT: Also servers can generate SQUIT messages on error conditions.
	return (0);
}

#include "ircserv.hpp"

void    create_server(Server *irc_server, uint16_t port) {
    struct rlimit       *resource_limit;
    getrlimit(RLIMIT_NOFILE, &resource_limit);

    int                 server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in  serv_addr;
    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    extern const int	backlog_to_listen;
    listen(server_socket, backlog_to_listen);

    Server("127.0.0.1", serv_addr.sin_port, 
        static_cast<intmax_t>(resource_limit.rlim_cur), server_socket);
}

int main(int argc, char *argv[]) {
    Server *irc_server = new Server();
    create_server(irc_server);
    delete irc_server;
    return (0);
}
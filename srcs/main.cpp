#include "ircserv.hpp"
#include <unistd.h>

int main(int argc, char *argv[]) {
    std::cout << "Starting ircserv" << std::endl;

    // Создаем сокет
    int listenfd;
    listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Привязываем к сокету ip и порт (делаем локальный сокет TCP сокетом)
    struct sockaddr_in serv_addr; // сокет для работы с протоколами IP
    
    // '''
    //    #include <netinet/in.h>
    //    struct sockaddr_in {
    //        short            sin_family;   // e.g. AF_INET
    //        unsigned short   sin_port;     // e.g. htons(3490)
    //        struct in_addr   sin_addr;     // see struct in_addr, below
    //        char             sin_zero[8];  // zero this if you want to
    //    };
    //    struct in_addr {
    //        unsigned long s_addr;  // load with inet_aton()
    //    };
    // '''

    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(10001); // convert values between host and network byte order: host mostly little-endian, network mostly big-endian
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // преобразует обычный вид IP-адреса cp (из номеров и точек) в двоичный код в сетевом порядке расположения байтов 
    // htonl(INADDR_ANY) if you want to bind to all interfaces - not just "localhost"
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // the details specified in the structure ‘serv_addr’ to the socket created in the step above.
    // The details include, the family/domain, the interface to listen on(in case the system has multiple interfaces to network) and the port on which the server will wait for the client requests to come.

    // Говорим, что теперь наш заведенный сокет будет слушать
    listen(listenfd, 10); // listen используется сервером, чтобы информировать ОС, что он ожидает ("слушает") запросы связи на данном сокете. 
    // Без такой функции всякое требование связи с этим сокетом будет отвергнуто. 
    // Первый аргумент - сокет для прослушивания, второй аргумент (backlog) - целое положительное число, определяющее, как много запросов связи может быть принято на сокет одновременно.

    

    // Устанавливаем соединение
    // Выделяем клиенту буфер для сохранения присланного им и последующей отправки
    char sendBuff[4096];
    int connectionfd;
    connectionfd = accept(listenfd, (struct sockaddr*) NULL, NULL); 
    while(1)
    {
        memset(sendBuff, '\0', 4096);
        // send(connectionfd, "Connected!", 12, 0);
        recv(connectionfd, sendBuff, 4096, 0);
        // and send that buffer to client
        write(connectionfd, sendBuff, 4096);
        printf("%s\n", sendBuff);
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", sendBuff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
    close(connectionfd);
    return (0);
}

/*
** https://man7.org/linux/man-pages/man2/socket.2.html 
** SOCK_NONBLOCK
              Set the O_NONBLOCK file status flag on the open file
              description (see open(2)) referred to by the new file
              descriptor.  Using this flag saves extra calls to fcntl(2)
              to achieve the same result.
*/
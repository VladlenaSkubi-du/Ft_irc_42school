
#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
    // int answer = 1;
    send(cs, ":sschmele 001 sschmele * \r\n", 29, 0);
//   reply(h, RPL_YOURHOST, "Your host is %s and is running version r2-rs501.",
//         h->server_ip);
    send(cs, "Welcome to IRC server!\n", 25, 0);
    // send(cs, "sschmele!sschmele@sschmele", 28, 0);
}


#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "bircd.h"

void			srv_accept(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	csin;
  socklen_t		csin_len;

  csin_len = sizeof(csin);
  cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
          // Putting socket in a non-blocking mode
        if (!(fcntl(cs, F_GETFL) & O_NONBLOCK)) {
          printf("non-blocking socket\n\t");
          X(-1, fcntl(cs, F_SETFL, O_NONBLOCK), "fcntl");
        }
  printf("New client #%d from %s:%d\n", cs, inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
  clean_fd(&e->fds[cs]);
  e->fds[cs].type = FD_CLIENT;
  e->fds[cs].fct_read = client_read;
  e->fds[cs].fct_write = client_write;
  e->fds[cs].fct_write(e, cs);
}

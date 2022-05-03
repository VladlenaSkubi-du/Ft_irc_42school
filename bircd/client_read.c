
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
  int	r;
  int	i;

  r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
  if (r <= 0)
    {
      close(cs);
      clean_fd(&e->fds[cs]);
      printf("client #%d gone away\n", cs);
    }
  else
    {
      char *message = NULL;
      if (strncmp(e->fds[cs].buf_read, "/msg", 4) == 0) {
        message = "There is a message!";
      }
      i = 0;
      while (i < e->maxfd)
	    {
	      if ((e->fds[i].type == FD_CLIENT) && (i != cs)) {
          if (message == NULL)
            send(i, e->fds[cs].buf_read, r, 0);
          else
            send(i, message, 21, 0);
        }
	        
	      i++;
	    }
    }
}

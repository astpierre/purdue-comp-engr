/* Generics */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>

/* Network */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUF_SIZE 512
#define MAXMSG 512
#define PORT 2091

int read_from_client(int filedes) {
  char buffer[MAXMSG];
  int nbytes;

  nbytes = read(filedes, buffer, MAXMSG);
  if (nbytes < 0) {
    /* Read error. */
    perror("read");
    exit(EXIT_FAILURE);
  }
  else if (nbytes == 0) return -1; /* End-of-file */
  else {
    /* Data read. */
    fprintf(stderr, "Server: got message: `%s'\n", buffer);
    return 0;
  }
}


/* Main entrypoint method */
int main(int argc, char *argv[]) {
  /* Use port 91 + 2000 = 2091 when testing on ECEgrid */
  int port = atoi(argv[1]);   // Port number server runs/listens on

  
  if (argc != 2) { /* Check for expected input */
    perror("Usage: ./httpserver <port>\n");
    return EXIT_FAILURE;
  }

  /* 
    When the file is successfully found by the server, send back an HTTP 200 
    OK response as follows with the encrypted contents of the file specified in 
    the HTTP absolute path 
      ex.
      HTTP/1.0 200 OK<CR><LF><CR><LF> 
      <contents of encrypted file requested...>
  */

  /* 
    When the file is not found by the server, send back a 404 not found HTTP response 
      ex.
      HTTP/1.0 404 Not Found<CR><LF><CR><LF>
  */

  /* 
    When the file doesn’t have public read permission, send back a 403 
    Forbidden HTTP response.
      ex.
      HTTP/1.0 403 Forbidden<CR><LF><CR><LF>
  */
  extern int make_socket(uint16_t port);
  int sock;
  fd_set active_fd_set, read_fd_set;
  int i;
  struct sockaddr_in clientname;
  size_t size;

  /* Create the socket and set it up to accept connections. */
  sock = make_socket(PORT);
  if (listen(sock, 1) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  /* Initialize the set of active sockets. */
  FD_ZERO(&active_fd_set);
  FD_SET(sock, &active_fd_set);

  while (1) {
    /* Block until input arrives on one or more active sockets. */
    read_fd_set = active_fd_set;
    if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
      perror("select");
      exit(EXIT_FAILURE);
    }

    /* Service all the sockets with input pending. */
    for (i = 0; i < FD_SETSIZE; ++i) {
      if (FD_ISSET(i, &read_fd_set)) {
        if (i == sock) {
          /* Connection request on original socket. */
          int new;
          size = sizeof(clientname);
          new = accept(sock,
                       (struct sockaddr *)&clientname,
                       &size);
          if (new < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
          }
          fprintf(stderr,
                  "Server: connect from host %s, port %hd.\n",
                  inet_ntoa(clientname.sin_addr),
                  ntohs(clientname.sin_port));
          FD_SET(new, &active_fd_set);
        }
        else {
          /* Data arriving on an already-connected socket. */
          if (read_from_client(i) < 0) {
            close(i);
            FD_CLR(i, &active_fd_set);
          }
        }
      }
    }
  }
return EXIT_SUCCESS;
}


//

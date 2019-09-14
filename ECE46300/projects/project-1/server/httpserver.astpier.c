/* Generics */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

/* Network */
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* Macro's and defines */
#define MAXLINE 512
#define LISTENQ 8 /*maximum number of client connections */

/* Function declarations */
int open_listenfd(int port);
void handle_client(int fd);


void handle_client(int fd) {
  char buf[MAXLINE];
  char * path = NULL;
  char forbidden_msg[] = "HTTP/1.0 403 Forbidden\r\n\r\n";
  char file_accessible_msg[] = "HTTP/1.0 200 OK\r\n\r\n";
  char not_found_msg[] = "HTTP/1.0 404 Not Found\r\n\r\n";

  read(fd, buf, MAXLINE);
  path = strtok(buf, " ");
  path = strtok(NULL, " ");
  if (access(path, F_OK) != 0) {
    write(fd, not_found_msg, strlen(not_found_msg));
  } else if (access(path, R_OK) != 0) {
    write(fd, forbidden_msg, strlen(forbidden_msg));
  } else {
    write(fd, file_accessible_msg, strlen(file_accessible_msg));
  }

  return;
}


/* Opens server's listening file-descriptor */
int open_listenfd(int port) {
  int listenfd, optval = 1;
  struct sockaddr_in serveraddr;

  /* Create a socket descriptor */
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return -1;

  /* Eliminates "Address already in use" error from bind. */
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                 (const void *)&optval, sizeof(int)) < 0)
  {  return -1;  }
  
  /* listenfd will be an endpoint for all requests to port for this host */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);
  if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
  {  return -1;  }

  /* Make it a listening socket ready to accept connection requests */
  if (listen(listenfd, LISTENQ) < 0) 
  {  return -1;  }

  return listenfd;
}


/* Main entrypoint method */
int main(int argc, char ** argv) {
  /* Use port 91 + 2000 = 2091 when testing on ECEgrid */
  int port = atoi(argv[1]); // Port number server runs/listens on
  int listenfd, connfd, clientlen;
  struct sockaddr_in clientaddr;
  char *haddrp;

  if (argc != 2) { /* Check for expected input */
    perror("Usage: ./httpserver <port>\n");
    return EXIT_FAILURE;
  }

  /* Open listening file-descriptor */
  listenfd = open_listenfd(port);

  /* Start the server loop */
  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);

    handle_client(connfd);
    close(connfd);
  }

  return EXIT_SUCCESS;
}

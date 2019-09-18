/* Generics */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

/* Network */
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* Macro's and defines */
#define _POSIX_SOURCE
#define MAXLINE 512
#define LISTENQ 8 /*maximum number of client connections */

/* Function declarations */
int kill(pid_t pid, int sig);
int open_listenfd(int port);
void handle_client(int fd);

/* Handle a client's request */
void handle_client(int fd) {
  char buf[MAXLINE];
  char * path = NULL;
  char * shift_char = NULL;
  int shift_number = 0, i = 0, cyph = 0;
  FILE * client_file = NULL;
  char forbidden_msg[] = "HTTP/1.0 403 Forbidden\r\n\r\n";
  char file_accessible_msg[] = "HTTP/1.0 200 OK\r\n\r\n";
  char not_found_msg[] = "HTTP/1.0 404 Not Found\r\n\r\n";

  read(fd, buf, MAXLINE-1);
  path = strtok(buf, " ");
  path = strtok(NULL, " ");
  shift_char = strtok(NULL, " ");
  shift_number = atoi(shift_char) % 26;

  if (access(path, F_OK) != 0) { /* File not found --> :(  */
    write(fd, not_found_msg, strlen(not_found_msg));
  } else if (access(path, R_OK) != 0) { /* Don't have the perms --> :| */
    write(fd, forbidden_msg, strlen(forbidden_msg));
  } else { /* OK, perform encryption --> :) */
    write(fd, file_accessible_msg, strlen(file_accessible_msg));
    client_file = fopen(path, "r");
    while (!feof(client_file)) { 
      bzero(buf, MAXLINE);
      fread(buf, sizeof(char), MAXLINE-1, client_file);
      
      while(buf[i] != '\0' && i < strlen(buf)) { /* Iterate over file contents in buffer */
        if (isalpha(buf[i])) { /* Only shift alphabet characters */
          if ((int)buf[i] >= (int)'a' && (int)buf[i] <= (int)'z') {
            cyph = (int)buf[i] - shift_number;
            if (cyph < (int)'a') {
              cyph = cyph + (int)'z' - (int)'a' + 1;
            }
            buf[i] = (char)cyph;
          } else if ((int)buf[i] >= (int)'A' && (int)buf[i] <= (int)'Z') {
            cyph = (int)buf[i] - shift_number;
            if (cyph < (int)'A') {
              cyph = cyph + (int)'z' - (int)'a' + 1;
            }
            buf[i] = (char)cyph;
          }
        }
        i++;
      }
      i = 0;
      write(fd, buf, strlen(buf));
    }
    fclose(client_file);
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
  int http_port = atoi(argv[1]); // Port number HTTP Caesar Cypher listens on
  int udp_port = atoi(argv[2]); // Port number UDP Ping Service listens on
  int http_sockfd, udp_sockfd, connfd, clientlen;
  struct sockaddr_in clientaddr;
  pid_t child_proc;
  fd_set active_fd_set, read_fd_set;

  if (argc != 3) { /* Check for expected input */
    perror("Usage: ./mult_service_server <HTTP-port> <UDP-port>\n");
    exit(1);
  }

  /* Open listening file-descriptor */
  FD_ZERO(&active_fd_set);
  http_sockfd = open_listenfd(http_port);
  FD_SET(http_sockfd, &active_fd_set);
  udp_sockfd = open_listenfd(udp_port);
  FD_SET(udp_sockfd, &active_fd_set);


  /* Start the server loop */
  while (1) {
    read_fd_set = active_fd_set;
    if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
        perror("select in main while loop");
        exit(EXIT_FAILURE);
    }
    for(i=0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, &read_fd_set)) {

        }
    }



    clientlen = sizeof(clientaddr);
    connfd = accept(listenfd, (struct sockaddr *)&clientaddr, (socklen_t *)&clientlen);
    if ((child_proc = fork()) == 0) { /* Child process (1/connection) */
      close(listenfd);
      handle_client(connfd);
      close(connfd);
      break;
    }
    close(connfd);
  }

  return EXIT_SUCCESS;
}

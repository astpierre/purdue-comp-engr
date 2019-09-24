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
#include <sys/select.h>

/* Macro's and defines */
#define _POSIX_SOURCE
#define MAXLINE 512
#define LISTENQ 12 /*maximum number of client connections */

/* Function declarations */
int open_listenfd(int port, char * mode);
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
int open_listenfd(int port, char * mode) {
  int listenfd, optval = 1;
  struct sockaddr_in serveraddr;

  switch(mode[0]) {
    case 'T':
      listenfd = socket(AF_INET, SOCK_STREAM, 0);
      break;
    case 'U':
      listenfd = socket(AF_INET, SOCK_DGRAM, 0);
      break;
    default:
      perror("Mode must be 'U', 'UDP', 'T', 'TCP'\n");
      return -1;
  }

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

  if (mode[0] == 'T') {
      /* Make it a listening socket ready to accept connection requests */
      if (listen(listenfd, LISTENQ) < 0) 
      {  return -1;  }
  }

  return listenfd;
}


/* Main entrypoint method */
int main(int argc, char ** argv) {
  int http_port = atoi(argv[1]); // Port number HTTP Caesar Cypher listens on
  int udp_port = atoi(argv[2]); // Port number UDP Ping Service listens on
  int http_sockfd, udp_sockfd, connfd, clientlen, maxfd, n;
  struct sockaddr_in clientaddr;
  struct hostent * hp;
  struct in_addr caddr;
  pid_t child_proc;
  fd_set active_fd_set;
  fd_set read_fd_set;
  char * buf[MAXLINE];
  char * token = NULL;
  unsigned int seq = 0;
  int i = 0;

  if (argc != 3) { /* Check for expected input */
    perror("Usage: ./mult_service_server <HTTP-port> <UDP-port>\n");
    exit(1);
  }

  /* Open listening file-descriptors */
  FD_ZERO(&active_fd_set);
  http_sockfd = open_listenfd(http_port, "TCP");
  FD_SET(http_sockfd, &active_fd_set);
  udp_sockfd = open_listenfd(udp_port, "UDP");
  FD_SET(udp_sockfd, &active_fd_set);
  if (http_sockfd >= udp_sockfd) {
    maxfd = http_sockfd + 1;
  } else {
    maxfd = udp_sockfd + 1;
  }

  /* Start the server loop */
  while (1) {
    seq = 0;
    read_fd_set = active_fd_set;
    if (select(maxfd, &read_fd_set, NULL, NULL, NULL) < 0) {
        perror("select in main while loop");
        exit(EXIT_FAILURE);
    }

    if (FD_ISSET(http_sockfd, &read_fd_set)) {
      clientlen = sizeof(clientaddr);
      connfd = accept(http_sockfd, (struct sockaddr *)&clientaddr, (socklen_t *)&clientlen);
      if ((child_proc = fork()) == 0) { /* Child process (1/connection) */
        close(http_sockfd);
        handle_client(connfd);
        close(connfd);
        break;
      }
      close(connfd);
    
    } 
    if (FD_ISSET(udp_sockfd, &read_fd_set)) {
      token = NULL;
      clientlen = sizeof(clientaddr);
      bzero(buf, MAXLINE);
      n = recvfrom(udp_sockfd, buf, 512, 0, (struct sockaddr *)&clientaddr, (socklen_t *)&clientlen);
      if (n < 0) perror("ERR recvfrom in main.");
      memcpy(&seq, buf+n-4, 4);
      fprintf(stdout, "%d\n", seq);

      return 0;
      
      token = strtok(buf, " ");
      
      inet_aton(token, &caddr);
      token = strtok(NULL, " ");
      seq = atoi(token);

      if ((hp = gethostbyaddr((const void *)&caddr,
                                sizeof(caddr),
                                AF_INET)) == NULL) {
          perror("ERR gethostbyaddr in main.");
      }
      
      snprintf(buf, MAXLINE-1, "%s %d", hp->h_name, seq+1);

      n = sendto(udp_sockfd, buf, MAXLINE-1, 0, (struct sockaddr *)&clientaddr, clientlen);
    }
  }

  return EXIT_SUCCESS;
}

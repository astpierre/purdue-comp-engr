/* Generics */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

/* Network */
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUF_SIZE 2048

// Function declarations
int GET(int socketfd, char * path);
int open_sockfd(char * hostname, int port);


/* Opens + returns a socket file descriptor */
int open_sockfd(char * hostname, int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv_addr;
  struct hostent * server;

  if (sockfd < 0) {
    perror("[open_sockfd] error opening socket");
    exit(0);
  }

  server = gethostbyname(hostname);
  if (server == NULL) {
    perror("[open_sockfd] error, no such host");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;

  bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(port);
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    return EXIT_FAILURE;
  }
  return sockfd;
}


/* Helper method to make a GET request to socket file descriptor */
int GET(int socketfd, char * path) {
  char req[1000] = {0};
  sprintf(req, "GET %s HTTP/1.0\r\n\r\n", path);
  return write(socketfd, req, strlen(req));
}


/* Main entrypoint method */
int main(int argc, char *argv[]) {
  int sockfd = 0;             // Socket file descriptor
  char * buf;                 // Buffer for reading
  buf = (char *)calloc(BUF_SIZE, sizeof(char)); // Init to 0
  char * nxt_file;            // Relative path to next file
  char * hostname = argv[1];  // Hostname
  int port = atoi(argv[2]);   // Port number
  char * rel_path = argv[3];  // Relative path to file
  
  if (argc != 4) { /* Check for expected input */
    perror("Usage: ./client <hostname> <port> <relative-path>\n");
    return EXIT_FAILURE;
  }

  /* Open the socket(ie. the file descriptor interface) */
  sockfd = open_sockfd(hostname, port);
  if (sockfd == EXIT_FAILURE) { /* Check failure */
    perror("[main] Server refused or socket failed to connect 1/2.\n");
    return EXIT_FAILURE;
  }
  
  /* GET the path to file from server */
  if (GET(sockfd, rel_path) == -1) {
    perror("[main] Bad GET request.\n");
    return EXIT_FAILURE;
  }

  char * substr;
  int flag = 0;
  while (read(sockfd, buf, BUF_SIZE-1) > 1) { /* Find the file path in response. */
    buf[BUF_SIZE-1] = '\0';
    if ((substr = strstr(buf, "\r\n\r\n")) != NULL) {
      flag = 1;
      nxt_file = (char *)calloc(strlen(substr)-4, sizeof(char));
      for (int i=0; i < strlen(substr)-4; i++) {
        strcpy(nxt_file+i, substr+i+4);
      }
    }

    fprintf(stdout, "%s", buf);
    bzero(buf, BUF_SIZE);
  }
  close(sockfd);

  /* Reconnect to socket */
  sockfd = open_sockfd(hostname, port);
  if (sockfd == EXIT_FAILURE) { /* Check failure */
    perror("[main] Server refused or socket failed to connect 2/2.\n");
    return EXIT_FAILURE;
  }

  /* GET the contents of file from server */
  if (GET(sockfd, nxt_file) == -1) {
    perror("[main] Bad GET request.\n");
    return EXIT_FAILURE;
  }

  while (read(sockfd, buf, BUF_SIZE-1) > 1) {
    buf[BUF_SIZE-1] = '\0';
    fprintf(stdout, "%s", buf);
    bzero(buf, BUF_SIZE);
  }

  close(sockfd);
  free(nxt_file);
  free(buf);

  return EXIT_SUCCESS;
}

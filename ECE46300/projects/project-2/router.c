#include "ne.h"
#include "router.h"
#include <pthread.h>

int main(int argc, char ** argv) {
    /* Get CLAs */
    if (argc != 5) {
        printf("Usage: ./router <router-ID> <NE-hostname> <NE-UDP-port> <router-UDP-port>\n");
        exit(-1);
    }
    int router_id = atoi(argv[1]);
    int ne_port = atoi(argv[3]);
    int router_port = atoi(argv[4]);
    int sockfd;
    struct sockaddr_in si_router;
    struct sockaddr_in si_ne;
    struct hostent * ne_host;
    char buf[PACKETSIZE];
        
    struct pkt_INIT_REQUEST init_req;
    init_req.router_id = router_id;
    
    /* Initialize UDP socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(-1);
    }
    
    bzero((char *) &si_router, sizeof(si_router));
    si_router.sin_family = AF_INET;
    si_router.sin_port = htons(router_port);
    si_router.sin_addr.s_addr =htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&si_router, sizeof(si_router)) < 0) {
        perror("bind");
        exit(-1);
    }

    bzero((char *) &si_ne, sizeof(si_ne));
    if ((ne_host = gethostbyname(argv[2])) == NULL) {
        perror("gethostbyname");
        exit(-1);
    }
    si_ne.sin_family = AF_INET;
    bcopy((char *)ne_host->h_addr,
          (char *)&si_ne.sin_addr.s_addr, ne_host->h_length);
    si_ne.sin_port = htons(ne_port);            // NE port

    /* Send INIT_REQUEST */
    /* INIT_REQUEST to NETWORK_EMULATOR */
    bzero(buf, PACKETSIZE);
    buf[0] = 'A';    
    if (sendto(sockfd, buf, (strlen(buf)+1), 0, (struct sockaddr *)&si_ne, sizeof(si_ne)) < 0) {
        perror("sendto");
        exit(-1);
    }
    
    /* Receive INIT_RESPONSE */
    /* INIT_RESPONSE from NETWORK_EMULATOR */
    for(;;) {
        fflush(stdout);
        if(recv_len = recvfrom(sockfd, buf, PACKETSIZE, 0, (struct sockaddr *)&si_ne, sizeof(si_ne)) < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }
        printf("Data: %s\n", buf);
        break;
    }


    /* Instantiate UDP FD polling thread */
    /* - wait to receive RT_UPDATE packet */
    /* - upon packet received, UpdateRoutes */
    /* - keep timestamp of last received update from neighbors */
    
    /* Instantiate timer thread */
    /* UPDATE_INTERVAL expires */
    /* 1. ConvertTabletoPkt() */
    /* 2. RT_UPDATE() sent to all neighbors */
    /* FAILURE_DETECTION */
    /* CONVERGE_TIMEOUT */

    close(sockfd);
    exit(0);
}
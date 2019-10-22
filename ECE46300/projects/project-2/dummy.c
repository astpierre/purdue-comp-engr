#include "ne.h"
#include "router.h"
#include <pthread.h>

int main(int argc, char ** argv) {
    /* Get CLAs */
    if (argc != 2) {
        printf("Usage: ./dummy <NE-UDP-port>\n");
        exit(-1);
    }
    int dummy_port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in si_me;
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    struct hostent * ne_host;
    char buf[PACKETSIZE];
    struct pkt_INIT_REQUEST router_pkt;
    
        
    /* Initialize UDP socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(-1);
    }
    
    bzero((char *) &si_me, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(dummy_port);
    si_me.sin_addr.s_addr =htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&si_me, sizeof(si_me)) < 0) {
        perror("bind");
        exit(-1);
    }

    bzero((char *) &si_other, sizeof(si_other));
    
    /* Receive INIT_RESPONSE */
    /* INIT_RESPONSE from NETWORK_EMULATOR */
    for(;;) {
        fflush(stdout);
        if(recvfrom(sockfd, &router_pkt, PACKETSIZE, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen) < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }
        printf("Data: %d\n", router_pkt.router_id);
        bzero(buf, PACKETSIZE);
        buf[0] = 'D';
        struct pkt_INIT_RESPONSE {
  unsigned int no_nbr; /* number of directly connected neighbors */
  struct nbr_cost nbrcost[MAX_ROUTERS]; /* array holding the cost to each neighbor */
};
        struct pkt_INIT_RESPONSE resp;
        resp.no_nbr = 2;
        struct nbr_cost n1;
        n1.nbr = 3;
        n1.cost = 11;
        resp.nbrcost[0] = n1;
        struct nbr_cost n2;
        n2.nbr = 4;
        n2.cost = 14;
        resp.nbrcost[1] = n2;

        if (sendto(sockfd, &resp, PACKETSIZE, 0, (struct sockaddr *)&si_other, slen) < 0) {
            perror("sendto");
            close(sockfd);
            exit(-1);
        }
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
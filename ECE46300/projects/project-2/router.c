#include "ne.h"
#include "router.h"
#include <pthread.h>
#include <string.h>

static clock_t _current_time = 0;
 

/* Create a timer thread */
/*void start_timer(int seconds) {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, thread_start_timer, (void*) seconds)) {
        perror("pthread_create");
        exit(-1);
    }
}*/
 

/* Start the timer in another thread */
/*int * thread_start_timer(void *secs) {
    int seconds = (int) secs;
    _current_time = clock() + seconds * CLOCKS_PER_SEC;
    // loop until the 10 seconds has reached 
    while(clock() < _current_time){}
    pthread_exit(NULL);
}*/

/*  */


/* Main method */
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
    int slen = sizeof(si_ne);
    struct hostent * ne_host;
    char buf[PACKETSIZE];
    
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
    struct pkt_INIT_REQUEST init_req;
    init_req.router_id = router_id;
    if (sendto(sockfd, &init_req, (sizeof(init_req)+1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
        perror("sendto");
        exit(-1);
    }
    
    /* Receive INIT_RESPONSE */
    /* INIT_RESPONSE from NETWORK_EMULATOR */
    fflush(stdout);
    struct pkt_INIT_RESPONSE init_resp;
    if(recvfrom(sockfd, &init_resp, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0) {
        perror("recvfrom");
        close(sockfd);
        exit(-1);
    }
    printf("Neighbors: %d\nNBR: %d,%d\n", init_resp.no_nbr, init_resp.nbrcost[0].nbr, init_resp.nbrcost[0].cost);

    /* Initialize routing table with INIT_RESPONSE */
    InitRoutingTbl (&init_resp, router_id);
    FILE * fp = fopen("test.log", "w");

    PrintRoutes(fp, 0);

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
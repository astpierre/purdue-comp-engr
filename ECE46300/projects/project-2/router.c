#include "ne.h"
#include "router.h"
#include <pthread.h>
#include <strings.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

/* Timeout globals */
int convergence_timeout = 0;
int update_timeout = 0;


int udp_update_polling() {
    struct pkt_RT_UPDATE update_packet;
    for (;;) {
        bzero((void *)update_packet, PACKETSIZE);
        if (recvfrom(sockfd, &update_packet, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }

        /* Initialize routing table with INIT_RESPONSE */
        ntoh_pkt_RT_UPDATE(&update_packet);
        if (UpdateRoutes(&update_packet) == 1) {
            //PrintRoutes(logfile, argv[1]);
            fflush(stdout);
            // Send update to neighbors
        }
    }
}



void timer_thread_manager() {
    convergence_timeout = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
    update_timeout = clock() + UPDATE_INTERVAL * CLOCKS_PER_SEC;
    int num_nbr = NumRoutes-1;

    for(i=0; i < num_nbr; i++) {
        router_nbr_watch[i].time = clock() + FAILURE_DETECTION * CLOCKS_PER_SEC;
        router_nbr_watch[i].id = routingTable[i+1].dest_id;
    }

    int current_time = clock();
    
    while(1) {
        current_time = clock();
        if (current_time > update_timeout) {
            printf("UPDATE_TIMEOUT\n")
            return;
        }

        current_time = clock();
        if (current_time > convergence_timeout) {
            printf("CONVERGENCE_TIMEOUT\n");
            return;
        }


        for(i=0; i<num_nbr; i++) {
            current_time = clock();
            if (current_time > router_nbr_watch[i]) {
                printf("UNINSTALL ROUTER ID=%d\n", router_nbr_watch[i].id);
            }
        }
    }
    return;
}



/* Main method */
int main(int argc, char **argv) {
    /* Get CLAs */
    if (argc != 5)
    {
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
    struct hostent *ne_host;
    char logfilename[20];
    FILE * fp = NULL;
    pthread_t udp_polling_thread, timer_thread;
    int udp_thread_ret_val, timer_thread_ret_val;

    /* Initialize UDP socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(-1);
    }

    bzero((char *)&si_router, sizeof(si_router));
    si_router.sin_family = AF_INET;
    si_router.sin_port = htons(router_port);
    si_router.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&si_router, sizeof(si_router)) < 0)
    {
        perror("bind");
        exit(-1);
    }

    bzero((char *)&si_ne, sizeof(si_ne));
    if ((ne_host = gethostbyname(argv[2])) == NULL)
    {
        perror("gethostbyname");
        exit(-1);
    }
    si_ne.sin_family = AF_INET;
    bcopy((char *)ne_host->h_addr,
            (char *)&si_ne.sin_addr.s_addr, ne_host->h_length);
    si_ne.sin_port = htons(ne_port); // NE port

    /* Send INIT_REQUEST */
    /* INIT_REQUEST to NETWORK_EMULATOR */
    struct pkt_INIT_REQUEST init_req;
    init_req.router_id = htonl(router_id);
    if (sendto(sockfd, &init_req, (sizeof(init_req) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0)
    {
        perror("sendto");
        exit(-1);
    }

    /* Receive INIT_RESPONSE */
    /* INIT_RESPONSE from NETWORK_EMULATOR */
    fflush(stdout);
    struct pkt_INIT_RESPONSE init_resp;
    if (recvfrom(sockfd, &init_resp, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0)
    {
        perror("recvfrom");
        close(sockfd);
        exit(-1);
    }
    
    /* Initialize routing table with INIT_RESPONSE */
    ntoh_pkt_INIT_RESPONSE(&init_resp);
    InitRoutingTbl(&init_resp, router_id);
    strcpy(logfilename, "router_");
    strcat(logfilename, argv[1]);
    strcat(logfilename, ".log");
    fp = fopen(logfilename, "w");
    PrintRoutes(fp, argv[1]);

    /* Initialize the failure detection table for neighboring routers */
    for(i=0; i<NumRoutes; i++) {
        router_nbr_watch[i] = 0;
    }

    /* Instantiate UDP FD polling thread */
    udp_thread_ret_val = pthread_create(&udp_polling_thread, NULL, udp_update_polling, NULL);

    /* Instantiate timer manager thread */
    timer_thread_ret_val = pthread_create(&timer_thread, NULL, timer_thread_manager, NULL);

    pthread_join(&udp_polling_thread, NULL);
    pthread_join(&timer_thread, NULL);

    close(sockfd);
    exit(0);
}
#include "ne.h"
#include "router.h"
#include <pthread.h>
#include <strings.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

/* Timeout globals */
int convergence_timeout = 0;
int update_timeout = 0;
struct nbr_watch {
    int timeout; 
    int id; 
};
struct nbr_watch * nbrs_watch = NULL;


int udp_update_polling() {
    struct pkt_RT_UPDATE update_packet;
    int i=0;
    int cost_to_sender = 0;
    for (;;) {
        bzero((void *)update_packet, PACKETSIZE);
        if (recvfrom(sockfd, &update_packet, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0) {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }

        /* Initialize routing table with INIT_RESPONSE */
        ntoh_pkt_RT_UPDATE(&update_packet);
        for (i=0; i<init_resp.no_nbr; i++) {
            if (nbrs_watch[i].id == update_packet.sender_id) {
                nbrs_watch[i].timeout = clock() + FAILURE_DETECTION * CLOCKS_PER_SEC;
            }
            if (init_resp.nbrcost[i].nbr == update_packet.sender_id) {
                cost_to_sender = init_resp.nbrcost[i].cost;
            }
        }

        if (UpdateRoutes(&update_packet, cost_to_sender, router_id) == 1) {
            convergence_timeout = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
            PrintRoutes(fp, router_id);
            fflush(stdout);
            
            // Send update to neighbors
            bzero((void *)&update_packet, PACKETSIZE);
            ConvertTabletoPkt(&update_packet, router_id);
            for (i=0; i<init_resp.no_nbr; i++) {
                update_packet.dest_id = init_resp.nbrcost[i].nbr;
                if (sendto(sockfd, &update_packet, (sizeof(update_packet) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
                    perror("sendto");
                    exit(-1);
                }
            }
        }
    }
}


void timer_thread_manager() {
    convergence_timeout = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
    update_timeout = clock() + UPDATE_INTERVAL * CLOCKS_PER_SEC;
    int current_time;
    int i=0;
    
    while(1) {
        convergence_timeout = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
        current_time = clock();
        if (current_time > update_timeout) {
            bzero((void *)&update_packet, PACKETSIZE);
            ConvertTabletoPkt(&update_packet, router_id);
            for (i=0; i<init_resp.no_nbr; i++) {
                update_packet.dest_id = init_resp.nbrcost[i].nbr;
                if (sendto(sockfd, &update_packet, (sizeof(update_packet) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
                    perror("sendto");
                    exit(-1);
                }
            }
            update_timeout = clock() + UPDATE_INTERVAL * CLOCKS_PER_SEC;
        }

        current_time = clock();
        if (current_time > convergence_timeout) {
            printf("CONVERGENCE_TIMEOUT\n");
        }


        for(i=0; i<sizeof(nbrs_watch)/sizeof(struct nbr_watch); i++) {
            current_time = clock();
            if (current_time > nbrs_watch[i].timeout) {
                printf("UNINSTALL ROUTER ID=%d\n", nbrs_watch[i].id);
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
    int i=0;

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
    
    ntoh_pkt_INIT_RESPONSE(&init_resp);
    /* Initialize the failure detection table for neighboring routers */
    nbrs_watch = calloc(init_resp.no_nbr, sizeof(struct nbr_watch));
    for (i=0; i<init_resp.no_nbr; i++) {
        nbrs_watch[i].id = init_resp.nbrcost[i].nbr;
        nbrs_watch[i].timeout = clock() + FAILURE_DETECTION * CLOCKS_PER_SEC;
    }

    /* Initialize routing table with INIT_RESPONSE */
    InitRoutingTbl(&init_resp, router_id);
    strcpy(logfilename, "router_");
    strcat(logfilename, argv[1]);
    strcat(logfilename, ".log");
    fp = fopen(logfilename, "w");
    PrintRoutes(fp, argv[1]);

    /* Instantiate UDP FD polling thread */
    udp_thread_ret_val = pthread_create(&udp_polling_thread, NULL, udp_update_polling, NULL);

    /* Instantiate timer manager thread */
    timer_thread_ret_val = pthread_create(&timer_thread, NULL, timer_thread_manager, NULL);

    pthread_join(&udp_polling_thread, NULL);
    pthread_join(&timer_thread, NULL);

    close(sockfd);
    close(fp)
    free(nbrs_watch);
    exit(0);
}
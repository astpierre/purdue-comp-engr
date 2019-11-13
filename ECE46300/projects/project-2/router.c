#include "ne.h"
#include "router.h"
#include <pthread.h>
#include <strings.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

/* Timeout Globals */
struct nbr_t {
    int timeout; 
    int id;
    int cost; 
};
struct timekeeper_t {
    int convergence;
    int update;
    struct nbr_t nbrs[MAX_ROUTERS-1];
    int q_nbrs;
};
struct timekeeper_t timekeeper;

/*  */
struct pkt_INIT_RESPONSE init_resp;
int router_id, ne_port, router_port, sockfd, slen;
struct sockaddr_in si_router;
struct sockaddr_in si_ne;
struct hostent * ne_host;
char logfilename[20];
FILE * fp;
int CONVERGED = 0;
pthread_mutex_t lock;



void udp_update_polling() {
    struct pkt_RT_UPDATE update_packet;
    int i=0;
    int cost_to_sender = 0;
    for (;;) {
        
        if (CONVERGED) {
            pthread_exit(NULL);
        }
        
        bzero((void *)&update_packet, PACKETSIZE);
        if (recvfrom(sockfd, &update_packet, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0) {
            perror("recvfrom");
            close(sockfd);
            return;
        }

        /* Process update */
        ntoh_pkt_RT_UPDATE(&update_packet);
        pthread_mutex_lock(&lock);
        for (i=0; i<timekeeper.q_nbrs; i++) {
            if (timekeeper.nbrs[i].id == update_packet.sender_id) {
                timekeeper.nbrs[i].timeout = clock() + FAILURE_DETECTION * CLOCKS_PER_SEC;
                cost_to_sender = timekeeper.nbrs[i].cost;
            }
        }
        pthread_mutex_unlock(&lock);

        pthread_mutex_lock(&lock);
        if (UpdateRoutes(&update_packet, cost_to_sender, router_id) == 1) {
            timekeeper.convergence = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
            PrintRoutes(fp, router_id);
            fflush(stdout);
            
            // Send update to neighbors
            bzero((void *)&update_packet, PACKETSIZE);
            ConvertTabletoPkt(&update_packet, router_id);
            for (i=0; i<init_resp.no_nbr; i++) {
                update_packet.dest_id = init_resp.nbrcost[i].nbr;
                hton_pkt_RT_UPDATE(&update_packet);
                if (sendto(sockfd, &update_packet, (sizeof(update_packet) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
                    perror("sendto");
                    return;
                }
            }
        }
        pthread_mutex_unlock(&lock);
    }
}


void timer_thread_manager() {
    timekeeper.convergence = clock() + CONVERGE_TIMEOUT * CLOCKS_PER_SEC;
    timekeeper.update = clock() + UPDATE_INTERVAL * CLOCKS_PER_SEC;
    int current_time;
    int i=0;
    struct pkt_RT_UPDATE update_packet;
    
    while(1) {
        /* ~~~~~~~ Update Interval ~~~~~~~ */
        pthread_mutex_lock(&lock);
        current_time = clock();
        if (current_time > timekeeper.update) {
            bzero((void *)&update_packet, PACKETSIZE);
            ConvertTabletoPkt(&update_packet, router_id);
            for (i=0; i<init_resp.no_nbr; i++) {
                update_packet.dest_id = init_resp.nbrcost[i].nbr;
                hton_pkt_RT_UPDATE(&update_packet);
                if (sendto(sockfd, &update_packet, (sizeof(update_packet) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
                    perror("sendto");
                    exit(-1);
                }
            }
            timekeeper.update = clock() + UPDATE_INTERVAL * CLOCKS_PER_SEC;
        }
        pthread_mutex_unlock(&lock);

        /* ~~~~~~~ Convergence Interval ~~~~~~~ */
        pthread_mutex_lock(&lock);
        current_time = clock();
        if (current_time > timekeeper.convergence) {
            fprintf(fp, "%d:Converged\n", current_time-timekeeper.convergence);
            PrintRoutes(fp, router_id);
            fflush(fp);
            CONVERGED = 1;
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock);

        /* ~~~~~~~ Failure Detection ~~~~~~~ */
        pthread_mutex_lock(&lock);
        for(i=0; i<timekeeper.q_nbrs; i++) {
            current_time = clock();
            if (current_time > timekeeper.nbrs[i].timeout) {
                UninstallRoutesOnNbrDeath(timekeeper.nbrs[i].id);
            }
        }
        pthread_mutex_unlock(&lock);
    }
    return;
}



/* Main method */
int main(int argc, char **argv) {
    /* Get CLAs */
    if (argc != 5) {
        printf("Usage: ./router <router-ID> <NE-hostname> <NE-UDP-port> <router-UDP-port>\n");
        exit(-1);
    }

    /* Assigning to globals */
    router_id = atoi(argv[1]);
    ne_port = atoi(argv[3]);
    router_port = atoi(argv[4]);
    slen = sizeof(si_ne);

    /* Local variables */
    pthread_t udp_polling_thread, timer_thread;
    int i=0;

    /* Initialize UDP socket */
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(-1);
    }

    bzero((char *)&si_router, sizeof(si_router));
    si_router.sin_family = AF_INET;
    si_router.sin_port = htons(router_port);
    si_router.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&si_router, sizeof(si_router)) < 0) {
        perror("bind");
        exit(-1);
    }

    bzero((char *)&si_ne, sizeof(si_ne));
    if ((ne_host = gethostbyname(argv[2])) == NULL) {
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
    if (sendto(sockfd, &init_req, (sizeof(init_req) + 1), 0, (struct sockaddr *)&si_ne, slen) < 0) {
        perror("sendto");
        exit(-1);
    }

    /* Receive INIT_RESPONSE */
    /* INIT_RESPONSE from NETWORK_EMULATOR */
    fflush(stdout);
    bzero((void *)&init_resp, sizeof(init_resp));
    if (recvfrom(sockfd, &init_resp, PACKETSIZE, 0, (struct sockaddr *)&si_ne, (socklen_t *)&slen) < 0) {
        perror("recvfrom");
        close(sockfd);
        exit(-1);
    }
    ntoh_pkt_INIT_RESPONSE(&init_resp);

    /* Initialize the failure detection table for neighboring routers */
    for (i=0; i<init_resp.no_nbr; i++) {
        timekeeper.nbrs[i].id = init_resp.nbrcost[i].nbr;
        timekeeper.nbrs[i].timeout = clock() + FAILURE_DETECTION * CLOCKS_PER_SEC;
        timekeeper.nbrs[i].cost = init_resp.nbrcost[i].cost;
    }
    timekeeper.q_nbrs = init_resp.no_nbr;

    /* Initialize routing table with INIT_RESPONSE */
    InitRoutingTbl(&init_resp, router_id);
    strcpy(logfilename, "router_");
    strcat(logfilename, argv[1]);
    strcat(logfilename, ".log");
    fp = fopen(logfilename, "w");
    PrintRoutes(fp, router_id);

    /* Initialize the mutex */
    pthread_mutex_init(&lock, NULL);

    /* Instantiate UDP FD polling thread */
    (void) pthread_create(&udp_polling_thread, NULL, udp_update_polling, NULL);

    /* Instantiate timer manager thread */
    (void) pthread_create(&timer_thread, NULL, timer_thread_manager, NULL);

    pthread_join(timer_thread, NULL);
    pthread_join(udp_polling_thread, NULL);
    pthread_exit(NULL);

    //close(sockfd);
    //close(fp);
    //free(nbrs_watch);
    exit(0);
}
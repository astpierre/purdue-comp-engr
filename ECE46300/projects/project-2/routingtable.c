#include "ne.h"
#include "router.h"


/* ----- GLOBAL VARIABLES ----- */
struct route_entry routingTable[MAX_ROUTERS];
static int NumRoutes = 0;


////////////////////////////////////////////////////////////////
void InitRoutingTbl (struct pkt_INIT_RESPONSE *InitResponse, int myID){
	for (int i=0; i < InitResponse->no_nbr; i++) {
		routingTable[NumRoutes].dest_id = InitResponse->nbrcost[i].nbr;
		routingTable[NumRoutes].next_hop = InitResponse->nbrcost[i].nbr;
		routingTable[NumRoutes].cost = InitResponse->nbrcost[i].cost;
		routingTable[NumRoutes].path_len = 1;
		routingTable[NumRoutes].path[0] = myID;
		routingTable[NumRoutes].path[1] = InitResponse->nbrcost[i].nbr;
		printf("%d,%d\n", routingTable[NumRoutes].dest_id, routingTable[NumRoutes].cost);
		NumRoutes+=1;
	}
	return;
}


////////////////////////////////////////////////////////////////
int UpdateRoutes(struct pkt_RT_UPDATE *RecvdUpdatePacket, int costToNbr, int myID){
	/* ----- ADD UNKNOWN DESTINATIONS ----- */
	for (int i=0; i < RecvdUpdatePacket->no_routes; i++) {
		if (myTableContains(RecvdUpdatePacket->route[i].dest_id)) {
			/* CHECK FOR BETTER PATH */
			continue;
		} else {
			/* ADD ROUTE TO MY TABLE */
			continue;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////
void ConvertTabletoPkt(struct pkt_RT_UPDATE *UpdatePacketToSend, int myID){
	/* ----- YOUR CODE HERE ----- */
	return;
}


////////////////////////////////////////////////////////////////
//It is highly recommended that you do not change this function!
void PrintRoutes (FILE* Logfile, int myID){
	/* ----- PRINT ALL ROUTES TO LOG FILE ----- */
	int i;
	int j;
	for(i = 0; i < NumRoutes; i++){
		fprintf(Logfile, "<R%d -> R%d> Path: R%d", myID, routingTable[i].dest_id, myID);

		/* ----- PRINT PATH VECTOR ----- */
		for(j = 1; j < routingTable[i].path_len; j++){
			fprintf(Logfile, " -> R%d", routingTable[i].path[j]);	
		}
		fprintf(Logfile, ", Cost: %d\n", routingTable[i].cost);
	}
	fprintf(Logfile, "\n");
	fflush(Logfile);
}


////////////////////////////////////////////////////////////////
void UninstallRoutesOnNbrDeath(int DeadNbr){
	/* ----- YOUR CODE HERE ----- */
	return;
}
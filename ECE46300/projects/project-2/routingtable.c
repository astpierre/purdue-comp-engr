#include "ne.h"
#include "router.h"


/* ----- GLOBAL VARIABLES ----- */
struct route_entry routingTable[MAX_ROUTERS];
static int NumRoutes = 0;

////////////////////////////////////////////////////////////////
int myTableContains(unsigned int router_id) {
	int i;
	for (i=0; i < NumRoutes; i++) {
		if (routingTable[i].dest_id == router_id) {
			return 1;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////
void InitRoutingTbl (struct pkt_INIT_RESPONSE *InitResponse, int myID){
	int i;
	bzero(&routingTable, sizeof(routingTable));

	routingTable[NumRoutes].dest_id = myID;
	routingTable[NumRoutes].next_hop = myID;
	routingTable[NumRoutes].cost = 0;
	routingTable[NumRoutes].path_len = 1;
	routingTable[NumRoutes].path[0] = myID;
	NumRoutes += 1;

	for (i=0; i < InitResponse->no_nbr; i++) {
		routingTable[NumRoutes].dest_id = InitResponse->nbrcost[i].nbr;
		routingTable[NumRoutes].next_hop = InitResponse->nbrcost[i].nbr;
		routingTable[NumRoutes].cost = InitResponse->nbrcost[i].cost;
		routingTable[NumRoutes].path_len = 2;
		routingTable[NumRoutes].path[0] = myID;
		routingTable[NumRoutes].path[1] = InitResponse->nbrcost[i].nbr;
		NumRoutes+=1;
	}
	return;
}


////////////////////////////////////////////////////////////////
int UpdateRoutes(struct pkt_RT_UPDATE *RecvdUpdatePacket, int costToNbr, int myID) {
	/* ----- ADD UNKNOWN DESTINATIONS ----- */
	int i;
	int j;
	int k;
	int m;
	int table_changed = 0;
	for (i=0; i < RecvdUpdatePacket->no_routes; i++) {
		if (myTableContains(RecvdUpdatePacket->route[i].dest_id)) {
			/* CHECK FOR BETTER PATH */
			int ignore = 0;
			/* Path vector rule */
			for (j=0; j < NumRoutes; j++) {
				ignore = 0;
				if (routingTable[j].cost > INFINITY) {
					routingTable[j].cost = INFINITY;
				}
				if (routingTable[j].dest_id == RecvdUpdatePacket->route[i].dest_id) {
					if (RecvdUpdatePacket->route[i].path_len == MAX_PATH_LEN) {
						routingTable[j].cost = INFINITY;
					} else {
						/* Path vector rule */
						for (k=0; k < RecvdUpdatePacket->route[i].path_len; k++) {
							if (RecvdUpdatePacket->route[i].path[k] == myID) {
								ignore = 1;
							}
						}
						if (ignore != 1) {
							if (routingTable[j].cost > (RecvdUpdatePacket->route[i].cost + costToNbr)) {
								routingTable[j].cost = RecvdUpdatePacket->route[i].cost + costToNbr;
								routingTable[j].next_hop = RecvdUpdatePacket->sender_id;
								routingTable[j].path_len = RecvdUpdatePacket->route[i].path_len + 1;
								routingTable[j].path[0] = myID;
								for (m=0; m < RecvdUpdatePacket->route[i].path_len; m++) {
									routingTable[j].path[m+1] = RecvdUpdatePacket->route[i].path[m];
								}
								table_changed = 1;
							}
						
							/* Forced update rule */
							if (routingTable[j].next_hop == RecvdUpdatePacket->sender_id) {
								if (RecvdUpdatePacket->route[i].cost > (routingTable[j].cost - costToNbr)) {
									routingTable[j].cost = RecvdUpdatePacket->route[i].cost + costToNbr;
									routingTable[j].path_len = RecvdUpdatePacket->route[i].path_len + 1;
									routingTable[j].path[0] = myID;
									for (m=0; m < RecvdUpdatePacket->route[i].path_len; m++) {
										routingTable[j].path[m+1] = RecvdUpdatePacket->route[i].path[m];
									}
									table_changed = 1;
								}
							}
						}
					}
				}
			}
		} else {
			/* ADD ROUTE TO MY TABLE */
			routingTable[NumRoutes].dest_id = RecvdUpdatePacket->route[i].dest_id;
			routingTable[NumRoutes].next_hop = RecvdUpdatePacket->route[i].path[0];
			routingTable[NumRoutes].cost = RecvdUpdatePacket->route[i].cost + costToNbr;
			routingTable[NumRoutes].path_len = RecvdUpdatePacket->route[i].path_len + 1;
			routingTable[NumRoutes].path[0] = myID;
			for (j=0; j < RecvdUpdatePacket->route[i].path_len; j++) {
				routingTable[NumRoutes].path[j+1] = RecvdUpdatePacket->route[i].path[j];
			}
			NumRoutes += 1;
			table_changed = 1;
		}
	}
	return table_changed;
}


////////////////////////////////////////////////////////////////
void ConvertTabletoPkt(struct pkt_RT_UPDATE *UpdatePacketToSend, int myID){
	int i;
	UpdatePacketToSend->sender_id = myID;
	UpdatePacketToSend->no_routes = NumRoutes;
	for (i=0; i < NumRoutes; i++) {
		UpdatePacketToSend->route[i] = routingTable[i];
	}
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
void UninstallRoutesOnNbrDeath(int DeadNbr) {
	int i, j;

	for (i = 0; i < MAX_ROUTERS; i++) {
		/* If DeadNbr, set cost to infinity */
		if (routingTable[i].dest_id == DeadNbr) {
			routingTable[i].cost = INFINITY;
			continue;
		}
		/* Not just for DeadNbr, check the path for DeadNbr */
		for (j = 0; j < routingTable[i].path_len; j++) {
			if (routingTable[i].path[j] == DeadNbr) {
				routingTable[i].cost = INFINITY;
				break;
			}
		}
	}
}
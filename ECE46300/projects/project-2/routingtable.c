#include "ne.h"
#include "router.h"
#include <strings.h>


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

	/* To avoid confusion */
	for (i=NumRoutes; i < MAX_ROUTERS; i++) {
		routingTable[i].dest_id = -1;
		routingTable[i].next_hop = -1;
		routingTable[i].cost = -1;
		routingTable[i].path[0] = -1;
		routingTable[i].path_len = -1;
	}

	return;
}


////////////////////////////////////////////////////////////////
/*int UpdateRoutes(struct pkt_RT_UPDATE *RecvdUpdatePacket, int costToNbr, int myID) {
	int i;
	int j;
	int k;
	int m;
	int table_changed = 0;
	for (i=0; i < RecvdUpdatePacket->no_routes; i++) {
		if (myTableContains(RecvdUpdatePacket->route[i].dest_id)) {
			int ignore = 0;
			for (j=0; j < NumRoutes; j++) {
				ignore = 0;
				if (routingTable[j].cost > INFINITY) {
					routingTable[j].cost = INFINITY;
				}
				if (routingTable[j].dest_id == RecvdUpdatePacket->route[i].dest_id) {
					if (RecvdUpdatePacket->route[i].path_len == MAX_PATH_LEN) {
						routingTable[j].cost = INFINITY;
					} else {
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
}*/

int UpdateRoutes(struct pkt_RT_UPDATE *RecvdUpdatePacket, int costToNbr, int myID) {
	/* ----- ADD UNKNOWN DESTINATIONS ----- */
	int i, j, k, m;
	int table_changed = 0;
	int ignore_route = 0;
	struct route_entry nbr_route;
	int forced_update = 0;
	int path_vector = 0;
	unsigned int old_cost = 0;
	unsigned int old_path_len = 0;
	unsigned int old_next_hop = 0; 

	
	for (i=0; i < RecvdUpdatePacket->no_routes; i++) {
		ignore_route = 0;
		forced_update = 0;
		path_vector = 0;
		old_cost = 0;
		old_path_len = 0;
		old_next_hop = 0;

		nbr_route = RecvdUpdatePacket->route[i];
		/* Add the route if it doesn't exist in my table */
		if (!myTableContains(nbr_route.dest_id)) {
			/* ADD ROUTE TO MY TABLE */
			routingTable[NumRoutes].dest_id = nbr_route.dest_id;
			routingTable[NumRoutes].next_hop = nbr_route.path[0];
			routingTable[NumRoutes].cost = nbr_route.cost + costToNbr;
			routingTable[NumRoutes].path_len = nbr_route.path_len + 1;
			routingTable[NumRoutes].path[0] = myID;
			for (j=0; j < nbr_route.path_len; j++) {
				routingTable[NumRoutes].path[j+1] = nbr_route.path[j];
			}
			NumRoutes += 1;
			table_changed = 1;
		} else {
			for (k=0; k < nbr_route.path_len; k++) {
				if (myID == nbr_route.path[k]) {
					ignore_route = 1;
				}
			}
			
			for (j=0; j < NumRoutes; j++) {
				if (routingTable[j].dest_id == nbr_route.dest_id) {
					break;
				}
			}
			
			if (routingTable[j].next_hop == RecvdUpdatePacket->sender_id) {
				if (nbr_route.cost > routingTable[j].cost) {
					forced_update = 1;
				}
			}
			
			if (ignore_route && !forced_update) {
				continue;
			}

			if ((costToNbr + nbr_route.cost) < routingTable[j].cost) {
				path_vector = 1;
			}

			if (forced_update || path_vector) {
				if (nbr_route.path_len == MAX_PATH_LEN) {
					routingTable[j].cost = INFINITY;
					routingTable[j].path_len = MAX_PATH_LEN;
					continue;
				}
				
				/* Save the prev vals for reference */
				old_cost = routingTable[j].cost;
				old_path_len = routingTable[j].path_len;
				old_next_hop = routingTable[j].next_hop;

				/* Do the update */
				routingTable[j].cost = nbr_route.cost + costToNbr;
				routingTable[j].next_hop = RecvdUpdatePacket->sender_id;
				routingTable[j].path_len = nbr_route.path_len + 1;
				routingTable[j].path[0] = myID;
				for (m=0; m < nbr_route.path_len; m++) {
					routingTable[j].path[m+1] = nbr_route.path[m];
				}
				if (routingTable[j].cost > (unsigned int)INFINITY)
				{
					routingTable[j].cost = (unsigned int)INFINITY;
				}

				if ((routingTable[j].cost != old_cost) || (routingTable[j].next_hop != old_next_hop) || (routingTable[j].path_len != old_path_len)) {
					table_changed = 1;
				}
			}
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
			routingTable[i].cost = (unsigned int)INFINITY;
			continue;
		}
		/* Not just for DeadNbr, check the path for DeadNbr */
		for (j = 0; j < routingTable[i].path_len; j++) {
			if (routingTable[i].path[j] == DeadNbr) {
				routingTable[i].cost = (unsigned int)INFINITY;
				break;
			}
		}
	}
}
#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt0;


void printdt0(struct distance_table *dtptr);

struct distance_table dist_table0;
/* students to write the following two routines, and maybe some others */
int min(int val1, int val2, int val3){
    int m;
    if(val1<=val2 && val1<=val3) m=val1;
    if(val2<val1 && val2<=val3) m=val2;
    if(val3<val1 && val3<val2) m=val3;
    return m;
}

void rtinit0()
{
    // fill own table with values


    int k;
    int j;
    for (k=0; k < 4; k++){ // initialize unkown values
        for (j=0; j < 4; j++){
            dist_table0.costs[k][j] = 999;
        }
    }
    dist_table0.costs[1][1] = 1;
    dist_table0.costs[2][2] = 3;
    dist_table0.costs[3][3] = 7;

    // init row to send
    struct rtpkt pkt;
    pkt.sourceid = 0;
    pkt.destid= 0;
    pkt.mincost[0] = 999;
    pkt.mincost[1] = 1;
    pkt.mincost[2] = 3;
    pkt.mincost[3] = 7;

    int i;
    for (i=1; i < 4; i++){ // send to all neighbors
        pkt.destid = i;
        tolayer2(pkt);
    }
    printdt0(&dist_table0);
}


void rtupdate0(struct rtpkt *rcvdpkt){
    int node=0,
	changed=0;
    int col = rcvdpkt->sourceid;
    int table_val, dest_val;
    int i;

    for(i=0; i<4; i++){
        if(i!=node) {
        table_val = dist_table0.costs[i][col];
        dest_val = rcvdpkt->mincost[i]+dist_table0.costs[col][col];
        if(dest_val < table_val) {
            dist_table0.costs[i][col] = dest_val;
            changed = 1;
	    }
        }

    }
    if(changed){
        struct rtpkt sendpkt;
        sendpkt.sourceid = node;
        printdt0(&dist_table0);
	int cost1,cost2,cost3;
	int k;

        for(k=0; k<4; k++){
            if(k != node){
		cost1 = dist_table0.costs[k][1];
		cost2 = dist_table0.costs[k][2];
		cost3 = dist_table0.costs[k][3];

                sendpkt.mincost[k]=min(cost1, cost2, cost3);
            }
	    else sendpkt.mincost[k]= 999;

        }
	sendpkt.destid = 1;
	tolayer2(sendpkt);

	sendpkt.destid = 2;
	tolayer2(sendpkt);

	sendpkt.destid = 3;
	tolayer2(sendpkt);
        printdt0(&dist_table0);
    }



}



void printdt0(struct distance_table *dtptr){
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost)


/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}


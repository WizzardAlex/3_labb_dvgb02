#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

void rtinit3()
{

    dt3.costs[0][0] = 7;
    dt3.costs[3][1] = 999;
    dt3.costs[2][2] = 2;
	int node = 3;

	int k;
    int j;
    for (k=0; k < 3; k++){ // initialize unkown values
		if (k != node){ // skips own row
			for (j=0; j < 3; j++){
				if(k!=j)	dt0.costs[k][j] = 999;
			}
		}
    }

    // init row to send
    struct rtpkt pkt;
    pkt.sourceid = node;
    pkt.destid= 0;
    pkt.mincost[0] = 7;
    pkt.mincost[1] = 999;
    pkt.mincost[2] = 2;
    pkt.mincost[3] = 0;

    int i;
    for (i=0; i < 3; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
}


void rtupdate3(struct rtpkt *rcvdpkt)


{

}


void printdt3(struct distance_table *dtptr)


{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}








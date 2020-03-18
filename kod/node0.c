#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

void printdt0(struct distance_table *dtptr);
struct distance_table
{
  int costs[4][4];
} dt0;


/* students to write the following two routines, and maybe some others */

void rtinit0()
{
    // fill own table with values
    dt0.costs[1][1] = 1;
    dt0.costs[2][2] = 3;
    dt0.costs[3][3] = 7;

    int k;
    int j;
    for (k=1; k < 3; k++){ // initialize unkown values
        for (j=0; j < 3; j++){
	    if(k!=j)	dt0.costs[k][j] = 999;
        }
    }

    // init row to send
    struct rtpkt pkt;
    pkt.sourceid = 0;
    pkt.destid= 0;
    pkt.mincost[0] = 0;
    pkt.mincost[1] = 1;
    pkt.mincost[2] = 3;
    pkt.mincost[3] = 7;

    int i;
    for (i=1; i < 3; i++){ // send to all neighbors
        pkt.destid = i;
        tolayer2(pkt);
    }
    printdt0(&dt0);
}


void rtupdate0(struct rtpkt *rcvdpkt)

{
}


void printdt0(struct distance_table *dtptr)


{
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


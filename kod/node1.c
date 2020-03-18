#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;



struct distance_table
{
  int costs[4][4];
} dt1;


/* students to write the following two routines, and maybe some others */


void rtinit1()
{
    // fill own table with values
    dt1.costs[0][0] = 1;
    dt1.costs[2][2] = 1;
    dt1.costs[3][3] = 999;

	int node = 1;

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
    pkt.mincost[0] = 1;
    pkt.mincost[1] = 0;
    pkt.mincost[2] = 1;
    pkt.mincost[3] = 999;

    int i;
    for (i=0; i < 3; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
}


void rtupdate1(struct rtpkt *rcvdpkt)


{

}


void printdt1(struct distance_table *dtptr)


{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}



#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;


struct distance_table
{
  int costs[4][4];
} dt1;

void printdist_table1(struct distance_table *dtptr);
struct distance_table dist_table1;
/* students to write the following two routines, and maybe some others */


void rtinit1()
{
    // fill own table with values
    dist_table1.costs[0][0] = 1;
    dist_table1.costs[2][2] = 1;
    dist_table1.costs[3][3] = 999;

	int node = 1;

    int k;
    int j;
    for (k=0; k < 4; k++){ // initialize unkown values
		if (k != node){ // skips own row
			for (j=0; j < 4; j++){
				if(k!=j)	dist_table1.costs[k][j] = 999;
			}
		}
    }

    // init row to send
    struct rtpkt pkt;
    pkt.sourceid = node;
    pkt.destid= 0;
    pkt.mincost[0] = 1;
    pkt.mincost[1] = 999;
    pkt.mincost[2] = 1;
    pkt.mincost[3] = 999;

    int i;
    for (i=0; i < 4; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
    printdist_table1(&dist_table1);
}


void rtupdate1(struct rtpkt *rcvdpkt)


{
    int col = rcvdpkt->sourceid;
    int table_val, dest_val;
    int i;

    for(i=0; i<4; i++){
	if(rcvdpkt->mincost[i] == 999 || i== 1) continue;
	table_val = dist_table1.costs[i][col];
	dest_val = rcvdpkt->mincost[i]+dist_table1.costs[col][col];
	if(dest_val<table_val) {
	    dist_table1.costs[i][col] = dest_val;
	}
    }
    printdist_table1(&dist_table1);

}


void printdist_table1(struct distance_table *dtptr)


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



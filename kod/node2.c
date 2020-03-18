#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt2;

void printdist_table2(struct distance_table *dtptr);
struct distance_table dist_table2;
/* students to write the following two routines, and maybe some others */

void rtinit2()
{
    dist_table2.costs[0][0] = 3;
    dist_table2.costs[1][1] = 1;
    dist_table2.costs[3][3] = 2;
    int node = 2;

    int k;
    int j;
    for (k=0; k < 3; k++){ // initialize unkown values
		if (k != node){ // skips own row
			for (j=0; j < 3; j++){
			    if(k!=j)	dist_table2.costs[k][j] = 999;
			}
		}
    }

    // init row to send
    struct rtpkt pkt;
    pkt.sourceid = node;
    pkt.destid= 0;
    pkt.mincost[0] = 3;
    pkt.mincost[1] = 1;
    pkt.mincost[2] = 0;
    pkt.mincost[3] = 2;

    int i;
    for (i=0; i < 3; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
    printdist_table2(&dist_table2);
}


void rtupdate2(struct rtpkt *rcvdpkt)


{

}


void printdist_table2(struct distance_table *dtptr)


{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}








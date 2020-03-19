#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt3;

void printdist_table3(struct distance_table *dtptr);
struct distance_table dist_table3;
/* students to write the following two routines, and maybe some others */

void rtinit3()
{

    dist_table3.costs[0][0] = 7;
    dist_table3.costs[3][1] = 999;
    dist_table3.costs[2][2] = 2;
	int node = 3;

	int k;
    int j;
    for (k=0; k < 4; k++){ // initialize unkown values
		if (k != node){ // skips own row
			for (j=0; j < 4; j++){
				if(k!=j)	dist_table3.costs[k][j] = 999;
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
    pkt.mincost[3] = 999;

    int i;
    for (i=0; i < 4; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
    printdist_table3(&dist_table3);
}


void rtupdate3(struct rtpkt *rcvdpkt)


{
    int col = rcvdpkt->sourceid;
    int table_val, dest_val;
    int i;

    for(i=0; i<4; i++){
        //if(rcvdpkt->mincost[i] == 999 || i == 3) continue;

        table_val = dist_table3.costs[i][col];
        dest_val = rcvdpkt->mincost[i]+dist_table3.costs[col][col];

        if(dest_val<table_val) {
            dist_table3.costs[i][col] = dest_val;
        }
	else if(table_val==999){
	    dist_table3.costs[i][col]= dist_table3.costs[col][col]*2+dist_table3.costs[i][i];
	}
    }
    printdist_table3(&dist_table3);
}


void printdist_table3(struct distance_table *dtptr)


{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}








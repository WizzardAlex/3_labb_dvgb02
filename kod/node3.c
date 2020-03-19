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
/*int min(int val1, int val2, int val3){
    int m;
    if(val1<=val2 && val1<=val3) m=val1;
    if(val2<val1 && val2<=val3) m=val2;
    if(val3<val1 && val3<val2) m=val3;
    return m;
}
*/


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

    int node=3;
    int changed=0;
    int col = rcvdpkt->sourceid;
    int table_val, dest_val;
    int i;

    for(i=0; i<4; i++){
	if(i==node) continue;
	table_val = dist_table3.costs[i][col];
	dest_val = rcvdpkt->mincost[i]+dist_table3.costs[col][col];
	if(dest_val<table_val) {
	    dist_table3.costs[i][col] = dest_val;
	    changed =1;
	}

    }
    if(changed){
	struct rtpkt sendpkt;
	sendpkt.sourceid=node;
	int j,k;
	int nodes[3];
	int cost1, cost2, cost3;
	for(j=0; j<4; j++){
		if(j!=node) nodes[j]= j;
	}


	for(k=0; k<4; k++){
	    if(i!=node){
		    sendpkt.destid=i;

		    printdist_table3(&dist_table3);
		    cost1=dist_table3.costs[i][0];
		    cost2=dist_table3.costs[i][1];
		    cost3=dist_table3.costs[i][2];
		    printf("%d\t%d\t%d\n",cost1,cost2,cost3);

		    sendpkt.mincost[i]=min(cost1 ,cost2, cost3);
		    printf("%d\n",sendpkt.mincost[i]);
	    }
	    else sendpkt.mincost[i] = 999;

	}
    printdist_table3(&dist_table3);
    tolayer2(sendpkt);
    }

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








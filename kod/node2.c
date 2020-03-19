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
/*int min(int val1, int val2, int val3){
    int m;
    if(val1<=val2 && val1<=val3) m=val1;
    if(val2<val1 && val2<=val3) m=val2;
    if(val3<val1 && val3<val2) m=val3;
    return m;
}
*/


void rtinit2()
{
    dist_table2.costs[0][0] = 3;
    dist_table2.costs[1][1] = 1;
    dist_table2.costs[3][3] = 2;
    int node = 2;

    int k;
    int j;
    for (k=0; k < 4; k++){ // initialize unkown values
		if (k != node){ // skips own row
			for (j=0; j < 4; j++){
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
    pkt.mincost[2] = 999;
    pkt.mincost[3] = 2;

    int i;
    for (i=0; i < 4; i++){ // send to all neighbors
		if (i != node){
			pkt.destid = i;
			tolayer2(pkt);
		}
	}
    printdist_table2(&dist_table2);
}

void rtupdate2(struct rtpkt *rcvdpkt)
{

    int node=2,
	changed=0;
    int col = rcvdpkt->sourceid;
    int table_val, dest_val;
    int i;

    for(i=0; i<4; i++){
	if(i==node) continue;
	table_val = dist_table2.costs[i][col];
	dest_val = rcvdpkt->mincost[i]+dist_table2.costs[col][col];
	if(dest_val<table_val) {
	    dist_table2.costs[i][col] = dest_val;
	    changed =1;
	}

    }
    if(changed){
	struct rtpkt sendpkt;
	sendpkt.sourceid=node;
	int j,k;
	int nodes[3];
	for(j=0; j<4; j++){
		if(j!=node) nodes[j]= j;
	}


	for(k=0; k<4; k++){
	    if(i!=node){
		sendpkt.destid=i;
		sendpkt.mincost[i]=min(dist_table2.costs[i][nodes[0]],dist_table2.costs[i][nodes[1]],dist_table2.costs[i][nodes[2]]);
		printf("%d\n",sendpkt.mincost[i]);
	    }
	    else sendpkt.mincost[i] = 999;

	}
    printdist_table2(&dist_table2);
    tolayer2(sendpkt);
    }

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








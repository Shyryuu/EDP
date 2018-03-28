#include "headers.h"

int worksplit(int start, int end,int P,int whoami,int *pos,int *who){

	int N=0,x=0,r=0,root;
	root=0;// primer procesador

	*pos.start=start;
	N=end-start;

	if(N<P) return(0); // not ok 
	if(end<start) return(0); // not ok

	for (int i =0; i<=P-1; ++i)
	{
		x=N/P;
		r=N%P;

		if (i<r){
			x=x+1;	
		}

		*pos.end=*pos.start+x-1;

		if (i==whoami){
			break;
		}

		*pos.start=*pos.end+1;	
	
	}

	return (1);
}

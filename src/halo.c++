#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

int halo(int N, double M[],double R[],double S[],int start, int end);


int main(int argc, char **argv)
{
	int N=3 ,mystart, myend,start=0,end=3,width,heigth;
	double *M,*R,*S;
	
	checkr(MPI_Init(&argc,&argv),"init");

	worksplit(start,end,quants(),whoami(),&mystart,&myend);

	width=N;
	heigth=myend-mystart+1;

	printf("mystart=%d myend=%d quants=%d quisoc=%d \n",mystart,myend,quants(),whoami());

	M=(double *)malloc(sizeof (double)*width*(heigth+2));
	R=(double *)malloc(sizeof (double)*width*1);
	S=(double *)malloc(sizeof (double)*width*1);

	if (M==NULL || R==NULL || S==NULL) 
    {
        printf("Out of memory\n");
        exit(1);
    }

	printf(" \n");

	if (halo(N,M,R,S,mystart,myend)==1)
	{
		for (int j = 0; j <heigth+1; ++j)
		{
			for (int  i=0; i<width; ++i)
			{
				printf("M=%f, i=%d j=%d \n",*(M+i+j*width),i,j);
			}	
		}
	}


	free (R);
	free (M);
	free (S);
	
	MPI_Finalize();

	exit (0);
}

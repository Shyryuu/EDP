#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

void checkr(int r,char *txt);
int quants();
int whoami();
int worksplit(int start, int end,int P,int whoami,int *mystart, int *myend);
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

	/*
	for (int j= 1; j <myend; ++j)
	{
		for (int  i=0; i<width; ++i)
			{
				*(M+i+j*width)=mystart+i+j;
				printf("M=%f, i=%d j=%d \n",*(M+i+j*width),i,j);
			}	
	}
	*/

	printf(" \n");

	if (halo(N,M,R,S,start,end)==1)
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


// funciones 

void checkr(int r,char *txt) {
  if (r!=MPI_SUCCESS) {
    fprintf(stderr,"Error: %s\n",txt);
    exit(-1);
  }
}

int quants() {
  int a,b;
  a=MPI_Comm_size(MPI_COMM_WORLD,&b);
  checkr(a,"quants");
  return(b);
}

int whoami() {
  int a,b;
  a=MPI_Comm_rank(MPI_COMM_WORLD,&b);
  checkr(a,"whoami");
  return(b);
}

int worksplit(int start, int end,int P,int whoami,int *mystart, int *myend){

	int N=0,x=0,r=0;

	*mystart=start;
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

		*myend=*mystart+x-1;

		if (i==whoami){
			break;
		}

		*mystart=*myend+1;	
	
	}
	return (1);
}

int halo(int N, double M[],double R[],double S[],int start,int end){

	int width,mystart,myend,heigth,h=1,k=0;

	width=N;

	worksplit(start,end,quants(),whoami(),&mystart,&myend);
	heigth=myend-mystart+1;


	if((quants()%2)==0)// comprovamos si habrá algún procesador suelto
	{
		//primero enviamos de pares y recivimos de los impares 

		if (whoami()%2==0)
			{	
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+myend)*width);
					}	
			}

			checkr(MPI_Ssend(S,width*h,MPI_INT,whoami()+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,whoami()+1,0,MPI_COMM_WORLD,&st),"receiving");	

				for (int jj = 0; jj<h; ++jj) // colocamos la información recivida por encima de la última fila
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj+myend+1)*width)=*(R+ii+(jj)*width);
					}	
				}

			}

		else {

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,whoami()-1,0,MPI_COMM_WORLD,&st),"receiving");

			for (int jj = 0; jj<h; ++jj) // copiamos la información que hemos recivido  en la primera fila
			{
				for (int ii=0; ii<width; ++ii)
				{
					*(M+ii+(jj)*width)=*(R+ii+(jj)*width);
				}	
			}
				
			for (int jj= 0; jj<h; ++jj) // copiamos la información que vamos a enviar de la fila 1
			{
				for (int ii=0; ii<width; ++ii)
				{
					*(S+ii+jj*width)=*(M+ii+(jj+h)*width);
				}	
			}

			checkr(MPI_Ssend(S,width*h,MPI_INT,whoami()-1,0,MPI_COMM_WORLD),"sending" );
	
			}	

	if (quants()>2){

			worksplit(start,end,quants(),whoami(),&mystart,&myend);

		//primero enviamos de pares y recivimos de los impares 

			if (whoami()%2!=0)
			{
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+myend)*width);
					}	
				}

			checkr(MPI_Ssend(S,width*h,MPI_INT,whoami()+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,whoami()+1,0,MPI_COMM_WORLD,&st),"receiving");	

				for (int jj = 0; jj<h; ++jj) // del vector R que mueve la información y lo ponemos en la última columna de la matriz M
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj+myend+1)*width)=*(R+ii+(jj)*width);
					}	
				}	
			}
	
			else {

				MPI_Status st;
				checkr(MPI_Recv(R,width*h,MPI_INT,whoami()-1,0,MPI_COMM_WORLD,&st),"receiving");

				for (int jj = 0; jj<h; ++jj) // copiamos la información que hemos recivido 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(M+ii+(jj)*width)=*(R+ii+(jj)*width);
					}	
				}
				
				for (int jj= 0; jj<h; ++jj) // copiamos la información que vamos a enviar 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(S+ii+jj*width)=*(M+ii+(jj+1)*width);
					}	
				}

				checkr(MPI_Ssend(S,width*h,MPI_INT,whoami()-1,0,MPI_COMM_WORLD),"sending" );

			}
		} 
		else
			printf("Solo hay quants=%d procesadores\n",quants());

		k=1;
	}

	else 
		{
			printf("Opción todavía no válida \n");
			k=0;
		}

	return k;
}
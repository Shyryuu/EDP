#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"
#include <string.h>

void checkr(int r,char *txt);
int quants();
int whoami();
int worksplit(int start, int end,int P,int whoami,int *mystart, int *myend);


int main(int argc, char **argv)
{
	checkr(MPI_Init(&argc,&argv),"init");

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

int halo(){

	int *m,*mystart,*myend,*R;// matriz local para poder mover los valores enviados 
	int width,n=10,h=1;
	worksplit();
	width=n;
	height=myend-mystart+1;


	if (quants()%2==0) // comprovamos si habrá algún procesador suelto 
	{
		for (int i = 0; i < quants(); i++)
		{
			worksplit(start,end,quants(),i,&mystart,&myend);

		//primero enviamos de pares y recivimos de los impares 

			if (whoami()%2==0)
			{
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(R+ii+j*width)=*(M+ii+(jj+myend)*width);
					}	
				}

			checkr(MPI_Ssend(R,width*h,MPI_INT,i+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,i+1,0,MPI_COMM_WORLD,&st),"receiving");	

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
				checkr(MPI_Recv(R,width*h,MPI_INT,i-1,0,MPI_COMM_WORLD,&st),"receiving");

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
						*(R+ii+jj*width)=*(M+ii+(jj+h)*width);
					}	
				}

				checkr(MPI_Ssend(R,width*h,MPI_INT,i-1,0,MPI_COMM_WORLD),"sending" );

			}
		}

		for (int i = 1; i < quants(); i++)
		{
			worksplit(start,end,quants(),i,&mystart,&myend);

		//primero enviamos de pares y recivimos de los impares 

			if (whoami()%2!=0)
			{
				for (int jj= 0; jj<h; ++jj) // copiamos la última fila para poder enviarla 
				{
					for (int ii=0; ii<width; ++ii)
					{
						*(m+ii+j*width)=*(M+ii+(jj+myend)*width);
					}	
				}

			checkr(MPI_Ssend(R,width*h,MPI_INT,i+1,0,MPI_COMM_WORLD),"sending" );

			MPI_Status st;
			checkr(MPI_Recv(R,width*h,MPI_INT,i+1,0,MPI_COMM_WORLD,&st),"receiving");	

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
				checkr(MPI_Recv(R,width*h,MPI_INT,i-1,0,MPI_COMM_WORLD,&st),"receiving");

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
						*(R+ii+j*width)=*(M+ii+(jj+1)*width);
					}	
				}

				checkr(MPI_Ssend(R,width*h,MPI_INT,i-1,0,MPI_COMM_WORLD),"sending" );

			}
		}

	}

	else
	{
		printf("Opción todavía no válida \n");
		return 0;
	}


}
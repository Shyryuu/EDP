
#include "EDP.h"
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv)
{
	checkr(MPI_Init(&argc,&argv),"init");

	srand (time(NULL)+rank())	;

	const int HALO_pool_size = 20;
	double mat[HALO_pool_size];

	double *p1,*p2,*p3;
	p1 = mat;
	p2 = mat+10;
	p3 = p2+10;

	for (int i = 0; i < HALO_pool_size/2; i++)
	{
		p2[i] = rand()%100;
	}

	HALO_update_data _HALO_data;
	HALO_update_unit _HALO_unit;

	_HALO_unit.partner = (rank()+1)%commsize();

	HALO_data_package send, receive;

	send.start = p2;
	send.end = p3;

	receive.start = p1;
	receive.end = p2;

	HALO_data_pair _p;

	_p.send = send;
	_p.receive = receive;

	_HALO_unit.package.push_back(_p);
	_HALO_data.push_back(_HALO_unit);

	HALO_update (_HALO_data);

	printf ("I'm processor %d and my data is: \n",rank());
	printf ("HALO: ");
	for (int i = 0; i < HALO_pool_size/2; i++)
	{
		printf("%f ",p1[i]);
	}
	printf ("\nDATA: ");
	for (int i = 0; i < HALO_pool_size/2; i++)
	{
		printf("%f ",p2[i]);
	}
	printf ("\n\n");

	MPI_Finalize();
	exit (0);
}

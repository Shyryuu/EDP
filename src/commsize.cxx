
#include "EDP.h"
#include "mpi.h"

int commsize()
{
	return(commsize(MPI_COMM_WORLD));
}

int commsize(MPI_Comm _comm)
{
	int b;
	checkr(MPI_Comm_size(_comm,&b),"");
  	return(b);
}

#include "EDP.h"
#include "mpi.h"
#include <stdlib.h>

void crash()
{
	MPI_Finalize();
	exit(-1);
}
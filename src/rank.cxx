
#include "EDP.h"
#include "mpi.h"

int rank()
{
  return(rank(MPI_COMM_WORLD));
}

int rank(MPI_Comm _comm) {
  int b;
  checkr(MPI_Comm_rank(_comm,&b), "Rank");
  return(b);
}
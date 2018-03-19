
#include "mpi.h"

void crash();

void checkr(int _MPI_Method);
void checkr(int _MPI_Method, const char* _error_message);

int commsize();
int commsize(MPI_Comm);

int rank();
int rank(MPI_Comm);
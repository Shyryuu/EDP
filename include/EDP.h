#include "mpi.h"
#include <vector>

void crash();

void checkr(int _MPI_Method);
void checkr(int _MPI_Method, const char* _error_message);

int commsize();
int commsize(MPI_Comm);

int rank();
int rank(MPI_Comm);

int worksplit(int start, int end,int P,int whoami,int *mystart, int *myend);

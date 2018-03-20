#include "mpi.h"
#include <vector>

struct HALO_data_package
{
	double *start, *end;
};

struct HALO_data_pair
{
	HALO_data_package send, receive;
};

struct HALO_update_unit
{
	unsigned int partner;
	std::vector<HALO_data_pair> package;
};

typedef std::vector<HALO_update_unit> HALO_update_data;

void crash();

void checkr(int _MPI_Method);
void checkr(int _MPI_Method, const char* _error_message);

int commsize();
int commsize(MPI_Comm);

int rank();
int rank(MPI_Comm);

int worksplit(int start, int end,int P,int whoami,int *mystart, int *myend);

int HALO_update(HALO_update_data);

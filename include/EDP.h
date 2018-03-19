
#include "mpi.h"
#include <vector>

void crash();

void checkr(int _MPI_Method);
void checkr(int _MPI_Method, const char* _error_message);

int commsize();
int commsize(MPI_Comm);

int rank();
int rank(MPI_Comm);

struct HALO_data_package
{
	double *start, *end;
};

struct HALO_update_unit
{
	unsigned int partner;
	std::vector<HALO_data_package> spackage;
	std::vector<HALO_data_package> rpackage;
};

typedef std::vector<HALO_update_unit> HALO_update_data;
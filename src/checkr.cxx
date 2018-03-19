
#include "EDP.h"
#include "mpi.h"

void checkr(int _MPI_Method)
{
	checkr(_MPI_Method, "Undefined error");
}

void checkr(int _MPI_Method, const char* _error_message)
{
	if (_MPI_Method!=MPI_SUCCESS)
	{
		fprintf(stderr,"Error: %s\n",_error_message);
    	crash();
	}
}
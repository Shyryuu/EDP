
#include "EDP.h"

using namespace std;

int HALO_update (HALO_update_data _update_data)
{
	int index = 0;
	// We iterate thorugh the main vector, so we make sure to communicate with all processes we need to
	for (auto it = _update_data.begin();it != _update_data.end(); it++)
	{
		// Now we iterate through ever communication pair. The HALO structures have to follow a logic so we don't end
		// up receiving/sending something when we dont have to.
		for (auto pit = it->package.begin(); pit!= it->package.end(); pit++)
		{
			MPI_Request req;
			MPI_Status st;

			checkr(MPI_Isend(pit->send.start, pit->send.end-pit->send.start,MPI_DOUBLE,it->partner,index,MPI_COMM_WORLD,&req), "Isend");
			checkr(MPI_Recv(pit->receive.start, pit->receive.end-pit->receive.start,MPI_DOUBLE,it->partner,index,MPI_COMM_WORLD,&st),"Recv");

		}

		index++;

	}
}
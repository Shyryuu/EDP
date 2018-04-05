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

int HALO_update(HALO_update_data);
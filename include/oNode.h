
#include <memory>	

public class oNode
{
protected:
	double *T;
	int nodeId;
	bool freeNode;

public:
	oNode(double, int, bool);
	oNode(double*, int, bool);

	int getTemp();
	void setTemp();
}
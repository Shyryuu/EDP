#include "oNode.h"

oNode::oNode(double T, int nodeId, bool freeNode = true) : nodeId(nodeId),freeNode(freeNode)
{
	T=new double; 
	*T=0;
}

oNode::oNode(double *T, int nodeId, bool freeNode = true) : T(T),nodeId(nodeId),freeNode(freeNode)
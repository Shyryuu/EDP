
class oNode;

public class oHaloRequest
{
protected:
	oNode* node;
	bool sender;

public:
	oHaloRequest(oNode* node, bool sender) : node(node), sender(sender)
	
}
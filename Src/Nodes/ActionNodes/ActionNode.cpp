#include "../../../Headers/Nodes/ActionNodes/ActionNode.hpp"

using namespace std;
ActionNode::ActionNode() {}

ActionNode::ActionNode(NodeId id, Cell *parentCell)
{
    if (id > 63)
    {
        throw std::logic_error("Wrong NodeId used during generation. InputNode cannot accept NodeType: " + id);
    }
}
#pragma endregion

#pragma region "Functions"
void ActionNode::Activate()
{
    switch(nodeId)
    {
        case ACTION_MFW: //Move forward

        break;
    }
}
#pragma endregion

//tanh(inputs) = range between -1 and 1
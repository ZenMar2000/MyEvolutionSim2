#include "../../../Headers/Nodes/ActionNodes/ActionNode.hpp"

using namespace std;
ActionNode::ActionNode() : Node() {}

ActionNode::ActionNode(NodeId id, Cell *parentCell) : Node(id, parentCell)
{
    if (id < 127 || id > 191)
    {
        throw std::logic_error("Wrong NodeId used during generation. ActionNode cannot accept NodeType: " + id);
    }
}
#pragma endregion

#pragma region "Functions"
void ActionNode::Activate()
{
    switch (nodeId)
    {
    case ACTION_MFW: // Move forward
        parentCell->WantToMove = true;
        break;
    }
}
#pragma endregion

// tanh(inputs) = range between -1 and 1
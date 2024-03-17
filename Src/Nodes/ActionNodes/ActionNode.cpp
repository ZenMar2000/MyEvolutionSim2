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
    NormalizeInputValue();
    if (NodeTriggered())
    {
        switch (nodeId)
        {
        case ACTION_TCW: // Turn clockwise
            parentCell->Turn(1);
            break;
        case ACTION_TCC: // Turn counter clockwise
            parentCell->Turn(-1);
            break;

        case ACTION_MFW: // Move forward
            parentCell->WantToMove = true;
            break;

        case ACTION_MBW:
            parentCell->WantToMove = true;
            parentCell->BackwardMove = true;
            break;
        }
    }

    Node::Activate();
}
#pragma endregion

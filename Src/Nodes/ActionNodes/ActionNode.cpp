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
            parentCell->DirectionalMove();
            break;

        case ACTION_MBW:
            parentCell->DirectionalMove(true);
            break;

        case ACTION_CXP:
            parentCell->CartesianMove(DIRECTION_E);
            break;

        case ACTION_CXN:
            parentCell->CartesianMove(DIRECTION_W);
            break;

        case ACTION_CYP:
            parentCell->CartesianMove(DIRECTION_S);
            break;

        case ACTION_CYN:
            parentCell->CartesianMove(DIRECTION_N);
            break;
        }
    }

    Node::Activate();
}
#pragma endregion

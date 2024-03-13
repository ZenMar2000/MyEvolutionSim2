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
        case ACTION_ADV: //advance

        break;

        case ACTION_PRM: //release pheromone
        break;

        case ACTION_TCC: //turn clockwise
        break;

        case ACTION_TCW: //turn counter clockwuse
        break;
    }
}
#pragma endregion
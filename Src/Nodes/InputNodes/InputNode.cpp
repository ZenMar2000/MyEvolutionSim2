#include "../../../Headers/Nodes/InputNodes/InputNode.hpp"
#pragma region "Constructors"
using namespace std;
InputNode::InputNode() : Node() {}

InputNode::InputNode(NodeId id, Cell *parentCell) : Node(id, parentCell)
{
    if (id > 63)
    {
        throw std::logic_error("Wrong NodeId used during generation. InputNode cannot accept NodeType: " + id);
    }
}
#pragma endregion

#pragma region "Functions"
void InputNode::AddToInput(double input)
{
    throw std::logic_error("Function 'InputToNode()' in InputNode.cpp not callable. InputNode class does not accept any input from other nodes.");
}

void InputNode::Activate()
{
    double output = 0;
    // Do specific action, selected by NodeId
    switch (nodeId)
    {
    case INPUT_RND:
        output = RND_Logic();
        break;

    case INPUT_BLK:
        output = BLK_Logic();
        break;

    default:
        output = 0;
        break;
    }

    // Write output data to all linked child nodes
    for (int i = 0; i < linkedChildNodes.size(); i++)
    {
        linkInfo info = linkedChildNodes.at(i);
        output *= info.invertedOutput ? -1 : 1;

        info.node->AddToInput(output * info.linkWeight);
    }
}
#pragma endregion

#pragma region "Protected Functions"
double InputNode::BLK_Logic()
{
    return parentCell->grid->CheckPosition(parentCell->cellPosition.GetSum(util->GetDirection(parentCell->GetDirectionIndex(0))));
}

double InputNode::RND_Logic()
{
    return util->GetRandomPercent();
}

#pragma endregion

// std::string binary = std::bitset<3>(7).to_string(); // to binary
// std::cout << binary << "\n";

// unsigned long decimal = std::bitset<4>(binary).to_ulong();
// std::cout << decimal << "\n";
// return 0;

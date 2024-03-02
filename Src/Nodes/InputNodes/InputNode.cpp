#include "../../../Headers/Nodes/InputNodes/InputNode.hpp"
#pragma region "Constructors"

InputNode::InputNode(){}

InputNode::InputNode(NodeType type, Cell *parentCell)
{
    if (type > 63)
    {
        throw std::logic_error("Wrong NodeType used during generation. InputNode cannot accept NodeType: " + type);
    }
}
#pragma endregion

#pragma region "Functions"
void InputNode::Activate()
{

}

int InputNode::GenerateNodeGenome()
{
    return 0;
}
#pragma endregion

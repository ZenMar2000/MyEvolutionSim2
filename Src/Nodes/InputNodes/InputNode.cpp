#include "../../../Headers/Nodes/InputNodes/InputNode.hpp"
#pragma region "Constructors"

InputNode::InputNode() : Node() {}

InputNode::InputNode(NodeType type, Cell *parentCell) : Node(type, parentCell)
{
    if(type > 63){
        throw std::logic_error("Wrong NodeType used during generation. InputNode cannot accept NodeType: " + type);
    }
   
}
#pragma endregion

#pragma region "Functions"

#pragma endregion

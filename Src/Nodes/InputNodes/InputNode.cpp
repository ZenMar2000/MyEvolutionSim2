#include "../../../Headers/Nodes/InputNodes/InputNode.hpp"
#pragma region "Constructors"
using namespace std;
InputNode::InputNode() {}

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

#pragma endregion

// std::string binary = std::bitset<3>(7).to_string(); // to binary
// std::cout << binary << "\n";

// unsigned long decimal = std::bitset<4>(binary).to_ulong();
// std::cout << decimal << "\n";
// return 0;

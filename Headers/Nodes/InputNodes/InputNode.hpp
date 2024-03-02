#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "../Node.hpp"

class InputNode : public Node
{
public:
#pragma region "Constructors"
    InputNode() : Node() {}

    InputNode(NodeType type, Cell *parentCell) : Node(type, parentCell){};
#pragma endregion

#pragma region "Functions"
    void Activate() override;

    int GenerateNodeGenome() override;
#pragma endregion
};

#endif
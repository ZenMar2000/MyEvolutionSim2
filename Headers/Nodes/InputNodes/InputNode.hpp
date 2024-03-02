#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "../Node.hpp"
class InputNode : public Node
{
public:
#pragma region "Constructors"
    InputNode();
    InputNode(NodeType type, Cell *parentCell);

#pragma endregion

#pragma region "Functions"
    virtual void Activate() override;
    virtual int GenerateNodeGenome() override;
#pragma endregion
};

#endif
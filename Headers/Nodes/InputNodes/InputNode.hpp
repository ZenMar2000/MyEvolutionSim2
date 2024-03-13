#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "../Node.hpp"
class InputNode : public Node
{
public:
#pragma region "Constructors"
    InputNode();
    InputNode(NodeId id, Cell *parentCell);

#pragma endregion

#pragma region "Functions"
    virtual void Activate() override;
    
#pragma endregion

};

#endif
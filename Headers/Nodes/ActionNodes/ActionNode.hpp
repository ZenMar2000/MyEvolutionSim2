#ifndef ACTIONNODE_H
#define ACTIONODE_H

#include "../Node.hpp"

class ActionNode : public Node
{
#pragma region "Constructors"
    ActionNode();
    ActionNode(NodeId id, Cell *parentCell);

#pragma endregion

#pragma region "Functions"
    virtual void Activate() override;
    
#pragma endregion

};

#endif
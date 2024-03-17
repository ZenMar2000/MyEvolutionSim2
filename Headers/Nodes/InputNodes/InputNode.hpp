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

#pragma region "Public Functions"
    void AddToInput(double input) override;
    void Activate() override;

#pragma endregion

protected:
#pragma region "Protected Functions"
    // Single functions that are used by the node
    // Selected based on NodeId inside Activate()
    double BLK_Logic();
    double RND_Logic();

#pragma endregion
};

#endif
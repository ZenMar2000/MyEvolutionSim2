#include <iostream>
#include "../../Headers/Nodes/Node.hpp"

#pragma region "Constructors"
Node::Node(){};

Node::Node(NodeType type, Cell *parentCell)
{
    this->parentCell = parentCell;
    nodeType = type;
}

Node::Node(NodeType type, Cell *parentCell, Node *parentNode)
{
    this->parentCell = parentCell;
    this->parentNode = parentNode;
    nodeType = type;
}
#pragma endregion

#pragma Region "Functions"
NodeType Node::GetNodeType()
{
    return nodeType;
}

void Node::AddLinkedNode(Node *node)
{
    linkedChildNodes.push_back(node);
}

void Node::RemoveLinkedNode(int index)
{
    int len = linkedChildNodes.size();

    if (len < 0)
    {
        cout << "'linkedNodes' list is empty" << endl;
        return;
    }
    else if (index < len - 1)
    {
        cout << "The given index is greater than linkedNodes list size" << endl;
        return;
    }

    list<Node *>::iterator it = linkedChildNodes.begin();
    advance(it, index);
    linkedChildNodes.erase(it);
}

void Node::Activate()
{
    throw std::logic_error("Function 'Activate()' in Node.cpp is not implemented. Please use derived classes instead.");
}

int Node::GenerateNodeGenome()
{
    throw std::logic_error("Function 'GenerateNodeGenome()' in Node.cpp is not implemented. Please use derived classes instead.");
}
#pragma endregion

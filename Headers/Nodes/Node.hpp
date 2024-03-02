#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include "../Utils.hpp"

using namespace std;

class Cell;


class Node
{
protected:
    bool invertedOutput;

    NodeType nodeType;
    Node *parentNode;
    list<Node *> linkedChildNodes;
    Utils *util;
    Cell *parentCell;

public:
#pragma region "Constructors"
    Node();
    Node(NodeType type, Cell* parentCell);
    Node(NodeType type, Cell* parentCell, Node *parentNode);

#pragma endregion

#pragma Region "Implemented Functions"
    // Get node id (used for genome generation)
    NodeType GetNodeType();

    // Add node to the linkedNodes list
    void AddLinkedNode(Node *node);

    // Remove node at specified index from the linkedNodes list
    void RemoveLinkedNode(int index);
#pragma endregion

#pragma region "Virtual Functions"
    // function that must be implemented in children classes
    virtual void Activate();
    virtual int GenerateNodeGenome();

#pragma endregion
};
#endif

// #ifndef HDC_H
// #define HDC_H

// #include "../Node.hpp"

// class InputNode_HDC: public Node{
//     public:
//     InputNode_HDC() : Node() {
//     }

//     InputNode_HDC() : Node (){
//         this-> nodeId = nodeId;
//         this-> nodeName = nodeName;
//         // this-> parentCell = parentCell;
//     }

//     void Activate() override{

//     }

//     int GenerateNodeGenome() override {

//     }
// };

// #endif
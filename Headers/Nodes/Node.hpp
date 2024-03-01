#ifndef NODE_H
#define NODE_H

#include "../Cell/Cell.hpp"

#include <iostream>
#include <list>
using namespace std;

class Node{
    protected:

    bool invertedOutput;
    int nodeId;
    char* nodeName;
    Node* parentNode;
    list<Node*> linkedNodes;
    // Cell* parentCell;

    public:

#pragma region "Constructors"
    Node();
    Node(Node* parentNode);
    // Node(Cell* parentCell, Node* parentNode);

#pragma endregion

#pragma Region "Implemented Functions"
    //Get node id (used for genome generation)
    int GetNodeId();

    //Get node name(for user understanding)
    char* GetNodeName();

    //Add node to the linkedNodes list
    void AddLinkedNode(Node* node);

    //Remove node at specified index from the linkedNodes list
    void RemoveLinkedNode(int index);

#pragma endregion

#pragma region "Virtual Functions"
    //function that must be implemented in children classes
    virtual void Activate();
    virtual int GenerateNodeGenome();

#pragma endregion

};
#endif

//Base INPUT NODE
// #ifndef 
// #define 
//
// #include "../Node.hpp"
//
// class InputNode_HDC: public Node{
//      public:
//      InputNode_HDC() : Node() {
//      }
//
//      InputNode_HDC(int nodeId, char* nodeName, Cell* parentCell) : Node (nodeId, nodeName, parentCell){
//          this-> nodeId = nodeId;
//          this-> nodeName = nodeName;
//          this-> parentCell = parentCell;
//      }
//
//      void Activate() override{
//
//      }
//
//      int GenerateNodeGenome() override {
//
//      }
// };

// #endif
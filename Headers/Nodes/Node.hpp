#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <bitset>
#include <vector>
#include <string>

#include "../Utils.hpp"

using namespace std;

class Cell;

class Node
{
public:
#pragma region "Constructors"
    Node();
    Node(NodeType type, Cell *parentCell);
    Node(NodeType type, Cell *parentCell, Node *parentNode);

#pragma endregion

#pragma Region "Functions"
 // Get node id (used for genome generation)
    NodeType GetNodeType();

    // Add node to the linkedNodes list
    void AddLinkedNode(Node *node);

    // Remove node at specified index from the linkedNodes list
    void RemoveLinkedNode(int index);

    // function that must be implemented in children classes
    virtual void Activate();

    // Get a vector containing all genomes of this node. Work only on Input an Neuron nodes. Action nodes does not have linked nodes.
    virtual vector<string> GetNodeGenome();

#pragma endregion

protected:
#pragma region "Variables for genome"
    bool invertedOutput;
    int linkWeight;
    NodeType nodeType;
    int genomeWeight;
    Node *parentNode;

    // vector containing all nodes linked to this node. They will get updated with the output value of this node.
    vector<Node *> linkedChildNodes;
#pragma endregion

#pragma region "Other variables"

    // vector containing the hexadecimal value of all genomes of this node
    vector<string> nodeGenomeList;
    Utils *util;
    Cell *parentCell;
#pragma endregion

    // Clear the vector nodeGenomeList and regenerate all genome by using genome variables and linkedChildNodes
    void GenerateNodeGenome();
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
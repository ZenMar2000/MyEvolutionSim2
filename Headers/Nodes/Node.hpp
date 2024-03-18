#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <bitset>
#include <vector>
#include <string>

#include "../Utils.hpp"
#include "../Cell/Cell.hpp"
using namespace std;

class Cell;
class Node
{

public:
    struct linkInfo
    {
        Node *linkedNode = NULL;
        double linkWeight = 0;
        bool invertedOutput = false;

        linkInfo(Node *newLinkedNode, double weight, bool inverted)
        {
            linkedNode = newLinkedNode;
            linkWeight = weight;
            invertedOutput = inverted;
        }
    };

#pragma region "Constructors"
    Node();
    Node(NodeId id, Cell *parentCell);

    // TODO Understand if useful
    Node(NodeId id, Cell *parentCell, Node *parentNode);
#pragma endregion

#pragma Region "Functions"
    // Get node id (used for genome generation)
    NodeId GetNodeId();

    // Add node to the linkedNodes list
    void AddLinkedNode(Node *nodeToLink, double linkWeight);

    // Remove node at specified index from the linkedNodes list
    void RemoveLinkedNode(int index);

    virtual void AddToInput(double input);

    // function that must be implemented in children classes
    virtual void Activate();

    // Get a vector containing all genomes of this node. Work only on Input an Neuron nodes. Action nodes does not have linked nodes.
    virtual vector<string> GetNodeGenome();

#pragma endregion

protected:
#pragma region "Variables for genome"
    NodeId nodeId = FREE;
    int genomeWeight = 0;
    Node *parentNode = NULL;

    double inputReceived = 0;

    // vector containing all nodes linked to this node. They will get updated with the output value of this node.
    vector<linkInfo> linkedChildNodes;

    // vector containing the hexadecimal value of all single genomes of this node
    vector<string> nodeGenomeList;
    Utils *util = NULL;
    Cell *parentCell = NULL;

#pragma endregion

#pragma region "Protected Functions"
    // Normalize variable inputReceived to a range between -1 and 1
    void NormalizeInputValue();
    bool NodeTriggered();

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

// #endif#pragma region "Structs"

#pragma endregion
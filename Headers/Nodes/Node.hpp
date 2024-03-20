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
        int nodeIndex;
        NodeType nodeType;
        double linkWeight = 0;
        bool invertedOutput = false;

        linkInfo() {}
        linkInfo(int linkedNodeIndex, NodeType linkedNodeType, double weight, bool inverted)
        {
            nodeIndex = linkedNodeIndex;
            nodeType = linkedNodeType;
            linkWeight = weight;
            invertedOutput = inverted;
        }
    };

#pragma region "Constructors"
    Node();
    Node(NodeId id, Cell *parentCell);

    // TODO Understand if useful
    // Node(NodeId id, Cell *parentCell, Node *parentNode);
#pragma endregion

#pragma Region "Functions"
    // Get node id (used for genome generation)
    NodeId GetNodeId();
    NodeType GetNodeType();

    // Add node to the linkedNodes list
    void AddLinkedNode(int nodeToLinkIndex, NodeType nodeToLinkType, double linkWeight, bool invertedLogic);

    // Remove node at specified index from the linkedNodes list
    void RemoveLinkedNode(int index);

    void AddToInput(double input);

    // function that must be implemented in children classes
    void ActivateBase();

    // Get a vector containing all genomes of this node. Work only on Input an Neuron nodes. Action nodes does not have linked nodes.
    virtual vector<string> GetNodeGenome();

#pragma endregion

protected:
#pragma region "Protected Variables"
    NodeId nodeId = FREE;
    NodeType nodeType = TYPE_FREE;

    double output = 0;
    double inputReceived = 0;

    int genomeWeight = 0;
    // Node *parentNode = NULL;

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

#pragma region "INPUT NODE"
    void Activate_InputNode();
    void HDP_Logic();
    void VDP_Logic();
    void HDO_Logic();
    void VDO_Logic();

    void FRC_Logic();
    void FRO_Logic();

    void BLK_Logic();
    void RND_Logic();
#pragma endregion

#pragma region "NEURON NODE"
    void Activate_NeuronNode();

#pragma endregion

#pragma region "ACTION NODE"
    void Activate_ActionNode();
#pragma endregion

#pragma endregion
};

#endif

#pragma endregion
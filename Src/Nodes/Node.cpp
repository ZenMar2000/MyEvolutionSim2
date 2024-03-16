
#include <iostream>
#include "../../Headers/Nodes/Node.hpp"

#pragma region "Constructors"
Node::Node(){};

Node::Node(NodeId id, Cell *parentCell)
{
    this->parentCell = parentCell;
    nodeId = id;
}

Node::Node(NodeId id, Cell *parentCell, Node *parentNode)
{
    this->parentCell = parentCell;
    this->parentNode = parentNode;
    nodeId = id;
}
#pragma endregion

#pragma Region "Functions"
NodeId Node::GetNodeId()
{
    return nodeId;
}

void Node::AddLinkedNode(Node *node, double linkWeight)
{
    NodeType nodeTp = util->GetNodeType(nodeId);
    if (nodeTp >= 3)
    {
        cout << "Current node " + to_string(nodeTp) + " cannot accept linked nodes. It's an Action or Free node" << endl;
        return;
    }
    linkedChildNodes.push_back(linkInfo(node, linkWeight, false));
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
    linkedChildNodes.erase(linkedChildNodes.begin() + index);
}

void Node::AddToInput(double input)
{
    inputReceived += input;
}

void Node::Activate()
{
    inputReceived = 0;
    // throw std::logic_error("Function 'Activate()' in Node.cpp is not implemented. Please use derived classes instead.");
}

vector<string> Node::GetNodeGenome()
{
    nodeGenomeList.clear();

    int genomeLen = sizeof(linkedChildNodes);
    string singleGenome;

    for (int i = 0; i < genomeLen; i++)
    {
        // Get binary value and convert in in Hexadecimal
        singleGenome = util->bin_to_hex(to_string(linkedChildNodes.at(i).invertedOutput) + bitset<3>(linkedChildNodes.at(i).linkWeight).to_string()) +
                       util->bin_to_hex(to_string(genomeWeight)) +
                       util->bin_to_hex(std::bitset<8>(nodeId).to_string()) +
                       util->bin_to_hex(std::bitset<8>(linkedChildNodes.at(i).node->GetNodeId()).to_string());
        nodeGenomeList.push_back(singleGenome);
    }

    return nodeGenomeList;
}

#pragma endregion

#pragma region "Protected Functions"
void Node::NormalizeInputValue()
{
    inputReceived = tanh(inputReceived);
}

bool Node::NodeTriggered()
{
    if (inputReceived > 0)
    {
        if (util->GetRandomPercent() <= inputReceived)
        {
            return false;
        }
    }
    return false;
}
#pragma endregion
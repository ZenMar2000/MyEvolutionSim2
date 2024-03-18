
#include <iostream>
#include "../../Headers/Nodes/Node.hpp"

#pragma region "Constructors"
Node::Node(){};

Node::Node(NodeId id, Cell *parentCell)
{
    this->parentCell = parentCell;
    nodeId = id;
    nodeType = util->GetNodeType(nodeId);
    linkedChildNodes.clear();
    inputReceived = 0;
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

NodeType Node::GetNodeType()
{
    return nodeType;
}

void Node::AddLinkedNode(Node *nodeToLink, double linkWeight)
{
    NodeType nodeTp = util->GetNodeType(nodeId);
    if (nodeTp >= 3)
    {
        cout << "Current node " + to_string(nodeTp) + " cannot accept linked nodes. It's an Action or Free node" << endl;
        return;
    }

    for (int i = 0; i < linkedChildNodes.size(); i++)
    {
        if (linkedChildNodes[i].linkedNode->GetNodeId() == nodeToLink->GetNodeId())
        {
            linkedChildNodes.erase(linkedChildNodes.begin() + i);
            break;
        }
    }
    linkedChildNodes.push_back(linkInfo(*nodeToLink, linkWeight, false));
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

void Node::ActivateBase()
{
    switch (nodeType)
    {
    case TYPE_INPUT:
        Activate_InputNode();
        break;

    case TYPE_NEURON:
        Activate_NeuronNode();
        break;

    case TYPE_ACTION:
        Activate_ActionNode();
        break;

    default:
        break;
    }

    inputReceived = 0;
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
                       util->bin_to_hex(std::bitset<8>(linkedChildNodes.at(i).linkedNode->GetNodeId()).to_string());
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
        double rnd = util->GetRandomPercent();
        if (rnd <= inputReceived)
        {
            return true;
        }
    }
    return false;
}

#pragma region "INPUT NODE"

void Node::Activate_InputNode()
{
    double output = 0;
    // Do specific action, selected by NodeId
    switch (nodeId)
    {
    case INPUT_RND:
        output = RND_Logic();
        break;

    case INPUT_BLK:
        output = BLK_Logic();
        break;

    default:
        output = 0;
        break;
    }

    // Write output data to all linked child nodes
    for (int i = 0; i < linkedChildNodes.size(); i++)
    {
        linkInfo &info = linkedChildNodes[i];
        output *= info.invertedOutput ? -1 : 1;

        info.linkedNode->inputReceived = (output * info.linkWeight);
    }
}

double Node::BLK_Logic()
{
    return parentCell->grid->CheckPosition(parentCell->cellPosition.GetSum(util->GetDirection(parentCell->GetDirectionIndex()))) == true ? 1 : 0;
}

double Node::RND_Logic()
{
    return util->GetRandomPercent();
}

#pragma endregion

#pragma region "NEURON NODE"
void Node::Activate_NeuronNode()
{
}
#pragma endregion

#pragma region "ACTION NODE"
void Node::Activate_ActionNode()
{
    NormalizeInputValue();
    if (NodeTriggered())
    {
        switch (nodeId)
        {
        case ACTION_TCW: // Turn clockwise
            parentCell->Turn(1);
            break;
        case ACTION_TCC: // Turn counter clockwise
            parentCell->Turn(-1);
            break;

        case ACTION_MFW: // Move forward
            parentCell->DirectionalMove();
            break;

        case ACTION_MBW:
            parentCell->DirectionalMove(true);
            break;

        case ACTION_CXP:
            parentCell->CartesianMove(DIRECTION_E);
            break;

        case ACTION_CXN:
            parentCell->CartesianMove(DIRECTION_W);
            break;

        case ACTION_CYP:
            parentCell->CartesianMove(DIRECTION_S);
            break;

        case ACTION_CYN:
            parentCell->CartesianMove(DIRECTION_N);
            break;
        }
    }
}
#pragma endregion
#pragma endregion
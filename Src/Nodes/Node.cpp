
#include <iostream>
#include "../../Headers/Nodes/Node.hpp"

#pragma region "Constructors"
Node::Node(){};

Node::Node(NodeId id, Cell *parentCell)
{
    this->parentCell = parentCell;
    nodeId = id;
    nodeType = util->GetNodeType(nodeId);

    {
        linkedChildNodes.push_back(linkInfo());
        linkedChildNodes.clear();

        inputReceived = 0;
    }
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

void Node::AddLinkedNode(int nodeToLinkIndex, NodeType nodeToLinkType, NodeId nodeToLinkId, double linkWeight, bool invertedLogic)
{
    NodeType nodeTp = util->GetNodeType(nodeId);
    if (nodeTp >= 3)
    {
        cout << "Current node " + to_string(nodeTp) + " cannot accept linked nodes. It's an Action or Free node" << endl;
        return;
    }

    // for (int i = 0; i < linkedChildNodes.size(); i++)
    // {
    //     if (parentCell->GenomeArray[linkedChildNodes[i].nodeType][linkedChildNodes[i].nodeIndex].GetNodeId() == parentCell->GenomeArray[nodeToLinkType][nodeToLinkIndex].GetNodeId())
    //     {
    //         linkedChildNodes.erase(linkedChildNodes.begin() + i);
    //         break;
    //     }
    // }

    linkInfo info = linkInfo(nodeToLinkIndex, nodeToLinkType, nodeToLinkId, linkWeight, invertedLogic);
    linkedChildNodes.push_back(info);
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

    int genomeLen = linkedChildNodes.size();
    string singleGenome;

    for (int i = 0; i < genomeLen; i++)
    {
        // Get binary value and convert in in Hexadecimal
        singleGenome = bitset<1>(linkedChildNodes[i].invertedOutput).to_string();
        singleGenome += bitset<3>(linkedChildNodes[i].linkWeight).to_string();
        singleGenome += std::bitset<4>(genomeWeight).to_string();
        singleGenome += std::bitset<8>(nodeId).to_string();
        singleGenome += std::bitset<8>(linkedChildNodes[i].linkedNodeId).to_string();

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
    // Do specific action, selected by NodeId
    switch (nodeId)
    {
    case INPUT_HDP:
        HDP_Logic();
        break;

    case INPUT_VDP:
        VDP_Logic();
        break;

    case INPUT_HDO:
        HDO_Logic();
        break;

    case INPUT_VDO:
        VDO_Logic();
        break;

    case INPUT_FRC:
        FRC_Logic();
        break;

    case INPUT_FRO:
        FRO_Logic();
        break;

    case INPUT_RND:
        RND_Logic();
        break;

    case INPUT_BLK:
        BLK_Logic();
        break;

    default:
        0;
        break;
    }

    // Write output data to all linked child nodes
    for (int i = 0; i < linkedChildNodes.size(); i++)
    {
        linkInfo info = linkedChildNodes[i];
        output *= info.invertedOutput ? -1 : 1;

        parentCell->GenomeArray[info.linkedNodeType][info.linkedNodeIndex].AddToInput(output * info.linkWeight);
    }

    output = 0;
}

void Node::HDP_Logic()
{
    output = util->GetWindowNormalizedDistance(parentCell->cellPosition, Vector2(0, parentCell->cellPosition.y));
}

void Node::VDP_Logic()
{
    output = util->GetWindowNormalizedDistance(parentCell->cellPosition, Vector2(parentCell->cellPosition.x, 0));
}

void Node::HDO_Logic()
{
    output = 1 - util->GetWindowNormalizedDistance(parentCell->cellPosition, Vector2(0, parentCell->cellPosition.y));
}

void Node::VDO_Logic()
{
    output = 1 - util->GetWindowNormalizedDistance(parentCell->cellPosition, Vector2(parentCell->cellPosition.x, 0));
}

void Node::FRC_Logic()
{
    output = parentCell->GetFoodReserve() / util->StartingFood;
}

void Node::FRO_Logic()
{
    output = 1 - (parentCell->GetFoodReserve() / util->StartingFood);
}

void Node::BLK_Logic()
{
    output = parentCell->grid->CheckPosition(parentCell->cellPosition.GetSum(util->GetDirection(parentCell->GetDirectionIndex()))) == true ? 1 : 0;
}

void Node::RND_Logic()
{
    output = util->GetRandomPercent();
}

#pragma endregion

#pragma region "NEURON NODE"
void Node::Activate_NeuronNode()
{
    double output = 0;
    NormalizeInputValue();

    for (int i = 0; i < linkedChildNodes.size(); i++)
    {
        linkInfo info = linkedChildNodes[i];
        output *= info.invertedOutput ? -1 : 1;

        parentCell->GenomeArray[info.linkedNodeType][info.linkedNodeIndex].AddToInput(output * info.linkWeight);
    }
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
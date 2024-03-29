#include "../../Headers/Cell/Cell.hpp"
#pragma region "Constructors"
Cell::Cell()
{
    cellPosition = Vector2(0, 0);
};

Cell::Cell(int genomeLength, Vector2 spawnPosition, Utils *util, DirectionsIndex direction, Grid *grid, int startingFood)
{
    cellPosition = spawnPosition;
    this->genomeLength = genomeLength;
    this->util = util;
    this->grid = grid;

    foodReserve = startingFood;
    directionIndex = (DirectionsIndex)(direction % util->DirectionsAmount);

    cellColor = util->GetRandomColor();

    // for (int i = 0; i < GenomeArray->size(); i++)
    // {
    //     GenomeArray[i].clear();
    // }
}


#pragma endregion

#pragma region "Public Functions"
void Cell::GenerateCell()
{
    vector<string> cellGenome;

    do
    {

        currentGenomeLength++;
    } while (currentGenomeLength < genomeLength);
}

void Cell::LoadCellGenome(vector<string> cellGenome)
{
    for (int i = 0; i < cellGenome.size(); i++)
    {
        LoadSingleCellGenome(cellGenome[i]);
    }
}

void Cell::LoadSingleCellGenome(string singleCellGenome)
{
    // TODO Add logic for checking if nodes already exists

    string binGenome[4];
    bool invertedLogic;
    int linkWeight;

    // Inverted logic and link weight
    binGenome[0] = util->hex_to_bin(singleCellGenome.substr(0, 1));

    invertedLogic = util->bin_to_int(binGenome[0].substr(0, 1)); // == "0" ? false : true;
    linkWeight = util->bin_to_int(binGenome[0].substr(1, 3));

    // Genome weight
    binGenome[1] = util->hex_to_bin(singleCellGenome.substr(1, 1));

    // Current node id
    binGenome[2] = util->hex_to_bin(singleCellGenome.substr(2, 2));

    // Node id linked to current node
    binGenome[3] = util->hex_to_bin(singleCellGenome.substr(4, 2));

    // Get current node type
    NodeId newCurrentNodeId = (NodeId)util->bin_to_int(binGenome[2]);
    NodeType newCurrentNodetype = util->GetNodeType(newCurrentNodeId);
    Node *currNode;

    // Get linked node type
    NodeId newLinkedNodeId = (NodeId)util->bin_to_int(binGenome[3]);
    NodeType newLinkedNodeType = util->GetNodeType(newLinkedNodeId);

    int linkedNodeIndex;

    // Check if currentNode already exists
    int nodeCheck = CheckIfNodeExists(newCurrentNodeId, newCurrentNodetype);
    if (nodeCheck == -1)
    {
        // Create and push_back the new node
        GenomeArray[newCurrentNodetype].push_back(Node(newCurrentNodeId, this));
        currNode = &GenomeArray[newCurrentNodetype].back();
    }
    else
    {
        // Node is already added, use it instead of creating a new one
        currNode = &GenomeArray[newCurrentNodetype][nodeCheck];
    }

    // Check if linkedNode already exists
    nodeCheck = CheckIfNodeExists(newLinkedNodeId, newLinkedNodeType);
    if (CheckIfNodeExists(newLinkedNodeId, newLinkedNodeType) == -1)
    {
        GenomeArray[newLinkedNodeType].push_back(Node(newLinkedNodeId, this));
        linkedNodeIndex = GenomeArray[newLinkedNodeType].size() - 1;
    }
    else
    {
        // Node is already added, use it instead of creating a new one
        linkedNodeIndex = nodeCheck;
    }

    currNode->AddLinkedNode(GenomeArray[newLinkedNodeType].size() - 1, newLinkedNodeType, newLinkedNodeId, linkWeight, invertedLogic);
}

void Cell::ClearCellGenome()
{
}

vector<string> Cell::GetCellGenome()
{
    vector<string> cellGenome;

    for (int nodeTypeIndex = TYPE_INPUT; nodeTypeIndex < TYPE_ACTION; nodeTypeIndex++)
    {
        if (GenomeArray[nodeTypeIndex].size() > 0)
        {
            for (int singleNodeIndex = 0; singleNodeIndex < GenomeArray[nodeTypeIndex].size(); singleNodeIndex++)
            {
                if (GenomeArray->size() <= 0)
                {
                    int i = 0;
                }

                vector<string> nodeGenome = GenomeArray[nodeTypeIndex][singleNodeIndex].GetNodeGenome();
                if (nodeGenome.size() > 0)
                {
                    for (int i = 0; i < nodeGenome.size(); i++)
                    {
                        string converted = "";

                        converted += util->bin_to_hex(nodeGenome[i].substr(0, 4));
                        converted += util->bin_to_hex(nodeGenome[i].substr(5, 4));
                        converted += util->bin_to_hex(nodeGenome[i].substr(8, 8));
                        converted += util->bin_to_hex(nodeGenome[i].substr(16, 8));

                        cellGenome.push_back(converted);
                    }
                }
            }
        }
    }

    return cellGenome;
}

bool Cell::IsAlive()
{
    return isAlive;
}

void Cell::SetCellColor(Color color)
{
    cellColor = color;
}

Color Cell::GetCellColor()
{
    return cellColor;
}

void Cell::PerformAction()
{
    if (foodReserve <= 0)
    {
        isAlive = false;
        return;
    }

    ActivateNodes(TYPE_INPUT);
    ActivateNodes(TYPE_NEURON);
    ActivateNodes(TYPE_ACTION);

    ReduceFood();
}

void Cell::DirectionalMove(bool isBackward)
{
    Vector2 newPos = cellPosition;

    newPos.Sum(util->GetDirection(GetDirectionIndex(isBackward ? 4 : 0)));

    // Check and fix movements outside grid
    grid->FixBorderCollisions(&newPos);

    // Check destination space if occupied
    if (grid->CheckIfCellSpaceFree(newPos))
    {
        grid->UpdateCollisionGrid(cellPosition, newPos);
        cellPosition.x = newPos.x;
        cellPosition.y = newPos.y;
    }
    CheckIfFoodReached();
}

void Cell::CartesianMove(DirectionsIndex directionIndex)
{
    Vector2 newPos = cellPosition;
    newPos.Sum(util->GetDirection(directionIndex));

    // Check and fix movements outside grid
    grid->FixBorderCollisions(&newPos);

    // Check destination space if occupied
    if (grid->CheckIfCellSpaceFree(newPos))
    {
        grid->UpdateCollisionGrid(cellPosition, newPos);
        cellPosition.x = newPos.x;
        cellPosition.y = newPos.y;
    }
    CheckIfFoodReached();
}

void Cell::CheckIfFoodReached()
{
    if (!grid->CheckIfFoodSpaceFree(cellPosition))
    {
        foodReserve += util->foodValue;
        grid->ResetFoodGridSpace(cellPosition);
    }
}

void Cell::Turn(int rotation)
{
    directionIndex = util->GetDirectionIndex((DirectionsIndex)(directionIndex + rotation));
}

DirectionsIndex Cell::GetDirectionIndex(int offset)
{
    return (DirectionsIndex)((directionIndex + offset) % util->DirectionsAmount);
}

int Cell::GetFoodReserve()
{
    return foodReserve;
}

int Cell::GetGenomeLength()
{
    return genomeLength;
}
#pragma endregion

#pragma region "Protected Functions"
// void Cell::LinkAllNodes(vector<string> cellGenome)
// {
// }

int Cell::CheckIfNodeExists(NodeId nodeId, NodeType nodeType)
{
    for (int i = 0; i < GenomeArray[nodeType].size(); i++)
    {
        if (GenomeArray[nodeType][i].GetNodeId() == nodeId)
        {
            return i;
        }
    }
    return -1;
}

void Cell::ReduceFood()
{
    if (util->foodEnabled)
    {
        foodReserve--;
    }
}

void Cell::ActivateNodes(NodeType type)
{
    for (int i = 0; i < GenomeArray[type].size(); i++)
    {
        GenomeArray[type][i].ActivateBase();
    }
}

#pragma endregion

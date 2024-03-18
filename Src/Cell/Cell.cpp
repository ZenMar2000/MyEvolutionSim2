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

    for (int i = 0; i < GenomeArray->size(); i++)
    {
        GenomeArray[i].clear();
    }
}

#pragma endregion

#pragma region "Public Functions"
void Cell::GenerateCellGenome()
{
    vector<string> cellGenome;

    do
    {

        currentGenomeLength++;
    } while (currentGenomeLength < genomeLength);
}

void Cell::LoadCellGenome(vector<string> cellGenome)
{
}

void Cell::ClearCellGenome()
{
}

vector<string> Cell::GetCellGenome()
{
    vector<string> cellGenome;
    for (int nodeTypeIndex = 0; nodeTypeIndex < 4; nodeTypeIndex++)
    {
        if (GenomeArray[nodeTypeIndex].size() > 0)
        {
            for (int singleNodeIndex = 0; singleNodeIndex < GenomeArray[nodeTypeIndex].size(); singleNodeIndex++)
            {
                vector<string> nodeGenome = GenomeArray[nodeTypeIndex][singleNodeIndex]->GetNodeGenome();
                if (nodeGenome.size() > 0)
                {
                    for (int i = 0; i < nodeGenome.size(); i++)
                    {
                        cellGenome.push_back(nodeGenome[i]);
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
}

void Cell::DirectionalMove(bool isBackward)
{
    Vector2 newPos = cellPosition;

    newPos.Sum(util->GetDirection(GetDirectionIndex(isBackward ? 4 : 0)));

    // Check and fix movements outside grid
    grid->FixBorderCollisions(&newPos);

    // Check destination space if occupied
    if (!grid->CheckIfSpaceOccupied(newPos))
    {
        grid->UpdateCollisionGrid(cellPosition, newPos);
        cellPosition.x = newPos.x;
        cellPosition.y = newPos.y;
    }
    ReduceFood();
}

void Cell::CartesianMove(DirectionsIndex directionIndex)
{
    Vector2 newPos = cellPosition;
    newPos.Sum(util->GetDirection(directionIndex));

    // Check and fix movements outside grid
    grid->FixBorderCollisions(&newPos);

    // Check destination space if occupied
    if (!grid->CheckIfSpaceOccupied(newPos))
    {
        grid->UpdateCollisionGrid(cellPosition, newPos);
        cellPosition.x = newPos.x;
        cellPosition.y = newPos.y;
    }
    ReduceFood();
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

#pragma endregion

#pragma region "Protected Functions"
void Cell::LinkAllNodes(vector<string> cellGenome)
{
}

void Cell::ReduceFood()
{
    foodReserve--;
}

void Cell::ActivateNodes(NodeType type)
{
    for (int i = 0; i < GenomeArray[type].size(); i++)
    {
        GenomeArray[type][i]->Activate();
    }
}

#pragma endregion

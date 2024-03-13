#include "../../Headers/Cell/Cell.hpp"
#pragma region "Constructors"
Cell::Cell()
{
    cellPosition = Vector2(0, 0);
};

Cell::Cell(int genomeLength, Vector2 spawnPosition, Utils *util, int startingFood)
{
    cellPosition = spawnPosition;
    this->genomeLength = genomeLength;
    this->util = util;
    // Genome = new Node[genomeLength]{};
    directionIndex = 3;
    foodReserve = startingFood;
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

void Cell::LoadSingleCellGenome(string singleCellGenome)
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
                vector<string> nodeGenome = GenomeArray[nodeTypeIndex][singleNodeIndex].GetNodeGenome();
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
    foodReserve--;
    if (foodReserve <= 0)
    {
        isAlive = false;
        return;
    }

    AdvanceForth();
    Turn(1);
}

void Cell::AdvanceForth()
{
    cellPosition.Sum(util->GetDirection(directionIndex));
}

void Cell::Turn(int rotation)
{
    directionIndex = util->GetDirectionIndex(directionIndex + rotation);
}
#pragma endregion

#pragma region "Protected Functions"
void Cell::LinkAllNodes(vector<string> cellGenome)
{
}
#pragma endregion

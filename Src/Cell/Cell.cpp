#include "../../Headers/Cell/Cell.hpp"

#pragma region "Constructors"
Cell::Cell()
{
    cellPosition = Vector2(0, 0);
};

Cell::Cell(int genomeLength, Vector2 spawnPosition, Utils *util)
{
    cellPosition = spawnPosition;
    this->genomeLength = genomeLength;
    this->util = util;
    Genome = new Node[genomeLength]{};
    direction = util->GetDirection(3);
}
#pragma endregion

#pragma region "Public Functions"
void Cell::GenerateGenome()
{
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
   cellPosition = cellPosition.Sum(direction);
}
#pragma endregion

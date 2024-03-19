#include "../../Headers/Grid/Grid.hpp"

#pragma region "Constructors"
int counter = 0;

Grid::Grid() {}
Grid::Grid(char *title, uint width, uint height, Utils *util)
{
    this->util = util;
    window = new SDLWindow(title, width, height);

    gridWidth = floor(width / util->CellPixelsDimension);
    gridHeight = floor(height / util->CellPixelsDimension);

    CellCollisionGrid.clear();
    FoodCollisionGrid.clear();
    // CellCollisionGrid = new bool *[gridWidth];
    // FoodCollisionGrid = new bool *[gridWidth];

    for (int w = 0; w < gridWidth; w++)
    {
        vector<bool> newVecCell;
        vector<bool> newVecFood;
        for (int h = 0; h < gridHeight; h++)
        {
            newVecCell.push_back(false);
            newVecFood.push_back(false);
        }

        CellCollisionGrid.push_back(newVecCell);
        FoodCollisionGrid.push_back(newVecFood);
    }
}

#pragma endregion

#pragma region "Public Functions"

void Grid::RefreshGrid()
{
    int cellCount = cellsInSimulation->size();
    // 1) Clear window graphic
    window->ClearWindow();

    // 2)Update cells raphical position
    if (cellCount > 0)
    {
        for (int i = 0; i < cellCount; i++)
        {
            Cell *c = &cellsInSimulation->at(i);
            if (c->IsAlive())
            {
                window->DrawPixel(c->GetCellColor(), c->cellPosition);
            }
        }
    }

    // 3) Update window Graphic
    window->UpdateWindow();
}

void Grid::SpawnCells(vector<Cell> &cellsAlive)
{
    cellsInSimulation = &cellsAlive;
    Cell c;
    for (int i = 0; i < cellsInSimulation->size(); i++)
    {
        c = cellsInSimulation->at(i);
        CellCollisionGrid[c.cellPosition.x][c.cellPosition.y] = true;
    }
}

void Grid::SpawnSingleCell(Cell cell)
{
    // cellsInSimulation->push_back(cell);
}

void Grid::SpawnFoodPips(){

};
void Grid::RespawnSingleFoodPip(){

};

bool Grid::CheckPosition(Vector2 position)
{
    FixBorderCollisions(&position);
    return (CheckIfInsideBorder(position) || CheckIfSpaceFree(position));
}

void Grid::FixBorderCollisions(Vector2 *position)
{
    if (position->x >= gridWidth)
        position->x = gridWidth - 1;
    else if (position->x < 0)
        position->x = 0;

    if (position->y >= gridHeight)
        position->y = gridHeight - 1;
    else if (position->y < 0)
        position->y = 0;
};

bool Grid::CheckIfSpaceFree(Vector2 position)
{
    bool ret = !CellCollisionGrid[position.x][position.y];
    return ret;
}

bool Grid::CheckIfInsideBorder(Vector2 position)
{
    if (position.x < gridWidth && position.x >= 0 && position.y < gridHeight && position.y >= 0)
    {
        return true;
    }
    return false;
}

void Grid::UpdateCollisionGrid(Vector2 oldPosition, Vector2 newPosition)
{
    CellCollisionGrid[oldPosition.x][oldPosition.y] = false;
    CellCollisionGrid[newPosition.x][newPosition.y] = true;
}

void Grid::SetGridSpace(Vector2 positionToSet)
{
    CellCollisionGrid[positionToSet.x][positionToSet.y] = true;
}
void Grid::ResetGridSpace(Vector2 positionToReset)
{
    CellCollisionGrid[positionToReset.x][positionToReset.y] = false;
}

#pragma endregion

#pragma region "Protected Functions"

#pragma endregion

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

void Grid::RefreshGrid(int currentSimulationStep, int currentGeneration)
{
    window->UpdateWindowTitle("MySim Generation " + to_string(currentGeneration) + " Step: " + to_string(currentSimulationStep) + "");
    // 1) Clear window graphic
    window->ClearWindow();

    // 2) Update food graphical position
    if (foodInSimulation->size() > 0)
    {

        if (util->foodEnabled)
        {
            for (int i = 0; i < foodInSimulation->size(); i++)
            {
                FoodElement *f = &foodInSimulation->at(i);

                if (CheckIfFoodSpaceFree(f->FoodPosition) && f->IsfoodRespawnable())
                {
                    Vector2 foodSpawnPos;
                    do
                    {
                        foodSpawnPos = Vector2(util->GetRandomInt(0, util->WindowWidth / util->CellPixelsDimension), util->GetRandomInt(0, util->WindowHeight / util->CellPixelsDimension));
                    } while (CheckIfCellSpaceFree(foodSpawnPos) == false && CheckIfFoodSpaceFree(foodSpawnPos) == false);

                    f->RespawnFood(foodSpawnPos);
                    SetFoodGridSpace(f->FoodPosition);
                }

                if (f->IsFoodEnabled())
                {
                    window->DrawPixel(FoodColor, f->FoodPosition);
                }
            }
        }
    }

    // 3)Update cells graphical position
    if (cellsInSimulation->size())
    {
        for (int i = 0; i < cellsInSimulation->size(); i++)
        {
            Cell *c = &cellsInSimulation->at(i);
            if (c->IsAlive())
            {
                window->DrawPixel(c->GetCellColor(), c->cellPosition);
            }
        }
    }
    // 4) Update window Graphic
    window->UpdateWindow();
}

void Grid::AddCellsToGrid(vector<Cell> &cellsAlive)
{
    cellsInSimulation = &cellsAlive;
    Cell c;
    for (int i = 0; i < cellsInSimulation->size(); i++)
    {
        c = cellsInSimulation->at(i);
        CellCollisionGrid[c.cellPosition.x][c.cellPosition.y] = true;
    }
}

void Grid::AddFoodToGrid(vector<FoodElement> &foodAvailable)
{
    foodInSimulation = &foodAvailable;
};

bool Grid::CheckPosition(Vector2 position)
{
    FixBorderCollisions(&position);
    return (CheckIfInsideBorder(position) || CheckIfCellSpaceFree(position));
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

bool Grid::CheckIfCellSpaceFree(Vector2 position)
{
    return !CellCollisionGrid[position.x][position.y];
}

bool Grid::CheckIfFoodSpaceFree(Vector2 position)
{
    return !FoodCollisionGrid[position.x][position.y];
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

void Grid::SetCellGridSpace(Vector2 positionToSet)
{
    CellCollisionGrid[positionToSet.x][positionToSet.y] = true;
}
void Grid::ResetCellGridSpace(Vector2 positionToReset)
{
    CellCollisionGrid[positionToReset.x][positionToReset.y] = false;
}

void Grid::SetFoodGridSpace(Vector2 positionToSet)
{
    FoodCollisionGrid[positionToSet.x][positionToSet.y] = true;
}
void Grid::ResetFoodGridSpace(Vector2 positionToReset)
{
    FoodCollisionGrid[positionToReset.x][positionToReset.y] = false;
}

#pragma endregion

#pragma region "Protected Functions"

#pragma endregion

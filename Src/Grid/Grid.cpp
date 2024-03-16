#include "../../Headers/Grid/Grid.hpp"

#pragma region "Constructors"
int counter = 0;

Grid::Grid() {}
Grid::Grid(char *title, uint width, uint height, Utils *util, vector<Cell> *cellsAlive)
{
    this->util = util;
    window = new SDLWindow(title, width, height);

    gridWidth = floor(width / util->CellPixelsDimension);
    gridHeight = floor(height / util->CellPixelsDimension);

    CellCollisionGrid = new bool *[gridWidth];
    FoodCollisionGrid = new bool *[gridWidth];

    for (int i = 0; i < gridWidth; i++)
    {
        CellCollisionGrid[i] = new bool[gridHeight];
        FoodCollisionGrid[i] = new bool[gridHeight];
    }

    SpawnCells(cellsAlive);
}

#pragma endregion

#pragma region "Public Functions"

void Grid::RefreshGrid()
{
    int cellCount = cellsInSimulation->size();
    // 1) Clear window graphic
    window->ClearWindow();

    // 2)Update cells graphic position
    if (cellCount > 0)
    {
        for (int i = 0; i < cellCount; i++)
        {
            Cell &c = cellsInSimulation->at(i);

            if (c.WantToMove)
            {
                Vector2 newPosition = c.cellPosition;
                newPosition.Sum(util->GetDirection(c.GetDirectionIndex()));

                int dirIndex = c.GetDirectionIndex();

                CheckBorderCollisions(newPosition);

                if (!CellCollisionGrid[newPosition.x][newPosition.y] || (newPosition.x == c.cellPosition.x && newPosition.y == c.cellPosition.y))
                {
                    CellCollisionGrid[c.cellPosition.x][c.cellPosition.y] = false;
                    CellCollisionGrid[newPosition.x][newPosition.y] = true;
                    c.MoveTo(newPosition);
                }

                // Vector2 dir = util->GetDirection(c->GetDirectionIndex());
                // Vector2 dest = c->cellPosition;
                // dest.Sum(dir);
                // c->MoveTo(dest);
            }

            window->DrawPixel(c.GetCellColor(), c.cellPosition);
        }
    }

    // 3) Update window Graphic
    window->UpdateWindow();
}

void Grid::SpawnCells(vector<Cell> *cellsAlive)
{
    cellsInSimulation = cellsAlive;
    for (int i = 0; i < cellsInSimulation->size(); i++)
    {
        Cell c = cellsInSimulation->at(i);
        CellCollisionGrid[c.cellPosition.x][c.cellPosition.y] = true;
    }
}

void Grid::SpawnSingleCell(Cell cell)
{
    cellsInSimulation->push_back(cell);
}
#pragma endregion

#pragma region "Protected Functions"
void Grid::CheckBorderCollisions(Vector2 &position)
{
    if (position.x >= gridWidth)
        position.x = gridWidth -1;
    else if (position.x < 0)
        position.x = 0;

    if (position.y >= gridHeight)
        position.y = gridHeight -1;
    else if (position.y < 0)
        position.y = 0;
};

#pragma endregion

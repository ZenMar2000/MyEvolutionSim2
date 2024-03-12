#include "../../Headers/Grid/Grid.hpp"

#pragma region "Constructors"
int counter = 0;
Grid::Grid() {}
Grid::Grid(char *title, uint width, uint height, Utils *util, vector<Cell> *cellsAlive)
{
    this->util = util;
    window = new SDLWindow(title, width, height);
    this->cellsAlive = cellsAlive;

    // gridWidth = floor(width / util->CellPixelsDimension);
    // gridHeight = floor(height / util->CellPixelsDimension);
}
#pragma endregion

#pragma region "Functions"

void Grid::RefreshGrid()
{
    int cellCount = cellsAlive->size();
    // 1) Clear window graphic
    window->ClearWindow();

    // 2)Move cells
    if (cellCount > 0)
    {
        for (int i = 0; i < cellCount; i++)
        {   
            Cell c = cellsAlive->at(i);
            window->DrawPixel(c.GetCellColor(),c.cellPosition);
        }
    }
    // 3) Update window Graphic
    window->UpdateWindow();
}
#pragma endregion
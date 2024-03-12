#include "../../Headers/Grid/Grid.hpp"

#pragma region "Constructors"
Grid::Grid(){}
Grid::Grid(char *title, uint width, uint height, Utils* util)
{
    this ->util = util;
    window = SDLWindow(title, width, height);

    gridWidth = floor(width/util->CellPixelsDimension);
    gridHeight = floor(height/util->CellPixelsDimension);

    gridArray = new int[gridWidth * gridHeight];

}
#pragma endregion

#pragma region "Functions"
#pragma endregion
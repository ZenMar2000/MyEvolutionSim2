#ifndef GRID_H
#define GRID_H

#include <vector>

#include "../Window/SDLWindow.hpp"
#include "../Utils.hpp"
#include "../Cell/Cell.hpp"

using namespace std;
class Grid
{
public:
#pragma region "Constructors"
    Grid();
    Grid(char *title, uint width, uint heightn, Utils *util, vector<Cell> *cellsAlive);

#pragma endregion

#pragma region "Public Functions"
    void RefreshGrid();

#pragma endregion

protected:
#pragma region "Protected Variables"
    //Object used ONLY for handling the graphic aspect
    SDLWindow *window;
    Utils *util;

    int gridWidth;
    int gridHeight;

    vector<Cell> *cellsAlive;

#pragma endregion
};

#endif
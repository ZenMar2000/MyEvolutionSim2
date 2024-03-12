#ifndef GRID_H
#define GRID_H

#include "../Window/SDLWindow.hpp"
#include "../Utils.hpp"

class Grid
{
public:
    Grid();
    Grid(char *title, uint width, uint heightn, Utils *util);

protected:
    int *gridArray;
    SDLWindow window;
    Utils *util;

    int gridWidth;
    int gridHeight;
};

#endif
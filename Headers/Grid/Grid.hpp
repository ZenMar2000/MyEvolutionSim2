#ifndef GRID_H
#define GRID_H

#include <vector>

#include "../Window/SDLWindow.hpp"
#include "../Utils.hpp"
#include "../Cell/Cell.hpp"

using namespace std;
class Cell;
class Grid
{
public:
#pragma region "Constructors"
    Grid();
    Grid(char *title, uint width, uint heightn, Utils *util, vector<Cell> *cellsAlive);

#pragma endregion

#pragma region "Public Functions"
    void RefreshGrid();

    void SpawnCells(vector<Cell> *cellsAlive);
    void SpawnSingleCell(Cell cell);

    void SpawnFoodPips(/* TODO ADD FOOD CLASS */);
    void RespawnSingleFoodPip(/* TODO ADD FOOD CLASS */);

    // Return true if position passed is occupied
    bool CheckIfSpaceOccupied(Vector2 position);

    // Return trurn true if position passed is outside grid
    bool CheckIfOutsideBorder(Vector2 position);

    // Check both if space occupied or if it's outside the grid.
    // Joined functions CheckIfSpaceOccupied() and CheckIfOutsideBorder()
    bool CheckPosition(Vector2 position);

#pragma endregion

protected:
#pragma region "Protected Variables"
    // Object used ONLY for handling the graphic aspect
    SDLWindow *window;
    Utils *util;

    int gridWidth;
    int gridHeight;

    vector<Cell> *cellsInSimulation;
    bool **CellCollisionGrid;
    bool **FoodCollisionGrid;

#pragma endregion

#pragma region "Protected Functions"

    // Check if movement goes out of grid. If true, fix it
    void FixBorderCollisions(Vector2 *position);

#pragma endregion
};

#endif
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
    Grid(char *title, uint width, uint heightn, Utils *util);

#pragma endregion

#pragma region "Public Functions"
    void RefreshGrid();

    void SpawnCells(vector<Cell> &cellsAlive);
    void SpawnSingleCell(Cell cell);

    void SpawnFoodPips(/* TODO ADD FOOD CLASS */);
    void RespawnSingleFoodPip(/* TODO ADD FOOD CLASS */);

    // Return true if position passed is free
    bool CheckIfSpaceFree(Vector2 position);

    // Return trurn true if position passed is inside grid
    bool CheckIfInsideBorder(Vector2 position);

    // Check both if space is free or if it's inside the grid.
    // Joined functions CheckIfSpaceOccupied() and CheckIfOutsideBorder()
    bool CheckPosition(Vector2 position);

    // Check if movement goes out of grid. If true, fix it
    void FixBorderCollisions(Vector2 *position);

    // Update collision grid. Used after a cell moved
    void UpdateCollisionGrid(Vector2 oldPos, Vector2 newPos);

    void SetGridSpace(Vector2 positionToSet);
    void ResetGridSpace(Vector2 positionToReset);

    void ClearFoodGridSpace(Vector2 positionToClear);

#pragma endregion

protected:
#pragma region "Protected Variables"
    // Object used ONLY for handling the graphic aspect
    SDLWindow *window;
    Utils *util;

    int gridWidth;
    int gridHeight;

    vector<Cell> *cellsInSimulation;
    vector<vector<bool>> CellCollisionGrid;
    vector<vector<bool>> FoodCollisionGrid;

#pragma endregion

#pragma region "Protected Functions"

#pragma endregion
};

#endif
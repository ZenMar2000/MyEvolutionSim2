#ifndef GRID_H
#define GRID_H

#include <vector>

#include "../Window/SDLWindow.hpp"
#include "../Utils.hpp"
#include "../Cell/Cell.hpp"
#include "../FoodElement/FoodElement.hpp"

using namespace std;
class Cell;
class Grid
{
public:
#pragma region "Public Variables"
    Color FoodColor = Color(255, 255, 255);

#pragma endregion

#pragma region "Constructors"
    Grid();
    Grid(char *title, uint width, uint heightn, Utils *util);

#pragma endregion

#pragma region "Public Functions"
    void RefreshGrid();

    void AddCellsToGrid(vector<Cell> &cellsAlive);
    void AddFoodToGrid(vector<FoodElement> &foodAvailable);

    // Return true if position passed is free
    bool CheckIfCellSpaceFree(Vector2 position);

    // Return true if position passed is free
    bool CheckIfFoodSpaceFree(Vector2 position);

    // Return trurn true if position passed is inside grid
    bool CheckIfInsideBorder(Vector2 position);

    // Check both if space is free or if it's inside the grid.
    // Joined functions CheckIfSpaceOccupied() and CheckIfOutsideBorder()
    bool CheckPosition(Vector2 position);

    // Check if movement goes out of grid. If true, fix it
    void FixBorderCollisions(Vector2 *position);

    // Update collision grid. Used after a cell moved
    void UpdateCollisionGrid(Vector2 oldPos, Vector2 newPos);

    void SetCellGridSpace(Vector2 positionToSet);
    void ResetCellGridSpace(Vector2 positionToReset);

    void SetFoodGridSpace(Vector2 positionToSet);
    void ResetFoodGridSpace(Vector2 positionToReset);
#pragma endregion

protected:
#pragma region "Protected Variables"
    // Object used ONLY for handling the graphic aspect
    SDLWindow *window;
    Utils *util;

    int gridWidth;
    int gridHeight;

    vector<Cell> *cellsInSimulation;
    vector<FoodElement> *foodInSimulation;

    vector<vector<bool>> CellCollisionGrid;
    vector<vector<bool>> FoodCollisionGrid;

#pragma endregion

#pragma region "Protected Functions"

#pragma endregion
};

#endif
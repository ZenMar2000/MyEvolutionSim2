#ifndef SIMHANDLER_H
#define SIMHANDLER_H

#include <vector>

#include "Cell/Cell.hpp"
#include "Grid/Grid.hpp"
#include "Utils.hpp"

using namespace std;

class SimulationHandler
{
public:
#pragma region "Public Variables"
    Utils Util = Utils();
#pragma endregion

#pragma region "Constructors"
    SimulationHandler();

#pragma endregion

#pragma region "Public Functions"
    void GenerateCell(Vector2 position, int direction);
    void Run();
#pragma endregion

protected:
#pragma region "Protected Variables"
    //Object containing generalized info of the cells. It prepares and feed data to the SDLWindow object.
    Grid grid = Grid();

    //Vector containing all cells currently alive. 
    //Used by this class to perform single cell actions 
    //  and from the grid to update the graphical position
    vector<Cell> cellsAlive;
    bool isRunning = false;

#pragma endregion

#pragma region "Protected Functions"
    void CheckIfExitRequested();
    void PerformCellActions();
    void CleanUpDeactivatedCells();
#pragma endregion
};

#endif
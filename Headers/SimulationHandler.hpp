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
    void GenerateCell();
    void Run();
#pragma endregion

protected:
#pragma region "Protected Variables"
    Grid grid = Grid();
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
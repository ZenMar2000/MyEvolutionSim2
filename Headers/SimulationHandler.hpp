#ifndef SIMHANDLER_H
#define SIMHANDLER_H

#include <vector>

#include "Cell/Cell.hpp"
#include "Grid/Grid.hpp"
#include "Utils.hpp"
#include "Nodes/Node.hpp"

using namespace std;

class SimulationHandler
{
public:
#pragma region "Public Variables"
    Utils Util = Utils();
#pragma endregion

#pragma region "Constructors"
    SimulationHandler(int maxCells, bool foodEnabled);

#pragma endregion

#pragma region "Public Functions"

    // Create a new cell
    void Run();
#pragma endregion

protected:
#pragma region "Protected Variables"
    // Object containing generalized info of the cells. It prepares and feed data to the SDLWindow object.
    Grid grid = Grid();

    // Vector containing all cells currently alive.
    // Used by this class to perform single cell actions
    //   and from the grid to update the graphical position
    vector<Cell> cellsAlive;
    bool isRunning = false;

    // vector<Cell> cellsPool;
    // int currentCellPoolIndex = 0;

    // Load a single Genome into the cell from hex values.

#pragma endregion

#pragma region "Protected Functions"
    // Instantiate all cells needed inside the vector cellsAlive. Must be called before GenerateCellGenome()
    void InstantiateCellVector(int maxCells);

    //Generate a Genome for a specific cell of the cellsAlive vector
    void GenerateCellGenome(Vector2 position, DirectionsIndex direction, int vectorPosition);

    void CheckIfExitRequested();

    //Trigger the cell brain, starting all checks and actions.
    void PerformCellActions();

    //remove a cell from the simulation
    void CleanUpDeactivatedCells();

    string BuildSingleGenome(bool invertedLogic, int linkWeight, int genomeWeight, NodeId firstNode, NodeId secondNode);
#pragma endregion
};

#endif
#ifndef SIMHANDLER_H
#define SIMHANDLER_H

#include <vector>

#include "Cell/Cell.hpp"
#include "Grid/Grid.hpp"
#include "Utils.hpp"

#include "Nodes/InputNodes/InputNode.hpp"
#include "Nodes/ActionNodes/ActionNode.hpp"
#include "Nodes/NeuronNodes/NeuronNode.hpp"

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
    void GenerateCell(Vector2 position, DirectionsIndex direction);
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

    // Load a single Genome into the cell from hex values.

#pragma endregion

#pragma region "Protected Functions"
    void CheckIfExitRequested();
    void PerformCellActions();
    void CleanUpDeactivatedCells();
    void LoadSingleCellGenome(string singleCellGenome, Cell *targetCell);
    void SpecializeNode(Node *nodeToSpecialize, NodeId nodeId, Cell *targetCell);
#pragma endregion
};

#endif
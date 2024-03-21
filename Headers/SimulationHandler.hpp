#ifndef SIMHANDLER_H
#define SIMHANDLER_H

#include <vector>

#include "Cell/Cell.hpp"
#include "Grid/Grid.hpp"
#include "Utils.hpp"
#include "Nodes/Node.hpp"
#include "FoodElement/FoodElement.hpp"

using namespace std;

class SimulationHandler
{
public:
#pragma region "Public Variables"
    Utils Util = Utils();
#pragma endregion

#pragma region "Constructors"
    SimulationHandler(int maxCells, int maxFood, bool foodEnabled);

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
    vector<FoodElement> foodAvailable;
    vector<Cell> survivors;
    bool isRunning = false;

    int winwidthUnit = 0;
    int winheightUnit = 0;

    int currentSimulationStep = 0;
    int simulationCutOff = 100;
    int currentGeneration = 0;
    int cellsAliveCounter = 0;
    int dimensionalCheck = 0;

#pragma endregion

#pragma region "Protected Functions"
    // Instantiate all cells needed inside the vector cellsAlive. Must be called before GenerateCell()
    void InstantiateCellVector(int maxCells);

    // Generate a cell with a random genome inside the cellsAlive vector
    void GenerateCell(DirectionsIndex direction, int vectorPosition);

    // Generate a cell with a specific genome inside the cellsAlive vector
    void GenerateCell(DirectionsIndex direction, int vectorPosition, vector<string> genome);

    void CheckIfExitRequested();

    // Trigger the cell brain, starting all checks and actions.
    void PerformCellActions();

    // remove a cell from the simulation
    void CleanUpDeactivatedCells();

    void InstantiateAllFood(int maxCells, int maxFood, int dimensionalCheck);

    string BuildSingleGenome(bool invertedLogic, int linkWeight, int genomeWeight, NodeId firstNode, NodeId secondNode);

    bool BeginNewGeneration();

    void SaveCurrentGeneration();

#pragma endregion
};

#endif
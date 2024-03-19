#include <iostream>

#include "../Headers/SimulationHandler.hpp"

#pragma region "Constructors"
SimulationHandler::SimulationHandler(int maxCells, bool foodEnabled)
{
    char *title = (char *)"MySim";
    grid = Grid(title, Util.WindowWidth, Util.WindowHeight, &Util);
    Util.foodEnabled = foodEnabled;

    cellsAlive.clear();

    InstantiateCellVector(maxCells);

    for (int i = 0; i < maxCells; i++)
    {
        GenerateCellGenome(Vector2(Util.GetRandomInt(0, Util.WindowWidth / Util.CellPixelsDimension),
                                   Util.GetRandomInt(0, Util.WindowHeight / Util.CellPixelsDimension)),
                           (DirectionsIndex)Util.GetRandomInt(0, 8),
                           i);
    }
}

#pragma endregion

#pragma region "Public Functions"
void SimulationHandler::Run()
{
    isRunning = true;
    grid.SpawnCells(cellsAlive);
    while (isRunning)
    {
        // Check if exit button pressed (escape button)
        CheckIfExitRequested();

        // Perform each cell action, depending on it's genome
        PerformCellActions();
        CleanUpDeactivatedCells();

        // refresh the graphical grid with updated positions of the cells
        grid.RefreshGrid();
    }
}

#pragma endregion

#pragma region "Protected Functions"

void SimulationHandler::InstantiateCellVector(int maxCells)
{
    for (int i = 0; i < maxCells; i++)
    {
        cellsAlive.push_back(Cell());
    }
}

void SimulationHandler::GenerateCellGenome(Vector2 position, DirectionsIndex direction, int vectorPosition)
{
    // TODO GENERATE RANDOM GENOME
    cout << &cellsAlive[vectorPosition] << endl;
    cellsAlive[vectorPosition] = Cell(5, position, &Util, direction, &grid, 50*vectorPosition);

    cellsAlive[vectorPosition].LoadSingleCellGenome("110C80");
    cellsAlive[vectorPosition].LoadSingleCellGenome("110D82");
    cellsAlive[vectorPosition].LoadSingleCellGenome("A10C82");

    // cellsAlive[vectorPosition].LoadCellGenome(vector<string>{"110C80", "110D82"});
}

void SimulationHandler::CheckIfExitRequested()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                isRunning = false;
            }
        }
    }
}

void SimulationHandler::PerformCellActions()
{
    int cellsCount = cellsAlive.size();
    if (cellsCount <= 0)
    {
        return;
    }

    for (int i = 0; i < cellsCount; i++)
    {
        cellsAlive[i].PerformAction();
    }
}

void SimulationHandler::CleanUpDeactivatedCells()
{
    int cellsCount = cellsAlive.size();
    if (cellsCount <= 0)
    {
        return;
    }

    for (int i = cellsCount - 1; i >= 0; i--)
    {
        if (!cellsAlive[i].IsAlive())
        {
            cellsAlive.erase(cellsAlive.begin() + i);
        }
    }
}

#pragma endregion

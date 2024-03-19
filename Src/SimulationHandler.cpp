#include <iostream>

#include "../Headers/SimulationHandler.hpp"

#pragma region "Constructors"
SimulationHandler::SimulationHandler(int maxCells, bool foodEnabled)
{
    Vector2 spawnPos;
    int winwidthUnit = Util.WindowWidth / Util.CellPixelsDimension;
    int winheightUnit = Util.WindowHeight / Util.CellPixelsDimension;
    char *title = (char *)"MySim";

    int dimensionalCheck = winwidthUnit * winheightUnit;
    dimensionalCheck *= 0.5;

    if (maxCells > dimensionalCheck)
    {
        throw std::logic_error("Error: maxCells specified in SimulationHandler constructor [" + to_string(maxCells) + "] is greater than maximum for this window resolution (it is equal to half of pixel resolution). Max cell available: [" + to_string(dimensionalCheck) + "]");
    }

    grid = Grid(title, Util.WindowWidth, Util.WindowHeight, &Util);
    Util.foodEnabled = foodEnabled;

    cellsAlive.clear();

    InstantiateCellVector(maxCells);

    for (int i = 0; i < maxCells; i++)
    {
        do
        {
            spawnPos = Vector2(Util.GetRandomInt(0, winwidthUnit), Util.GetRandomInt(0, winheightUnit));
        } while (grid.CheckIfSpaceFree(spawnPos) != true);

        GenerateCellGenome(spawnPos, (DirectionsIndex)Util.GetRandomInt(0, 8), i);
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

    // Create new cell and set space in grid as occupied
    cellsAlive[vectorPosition] = Cell(5, position, &Util, direction, &grid, 100);
    grid.SetGridSpace(cellsAlive[vectorPosition].cellPosition);

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
        if (!cellsAlive[i].IsAlive() && cellsAlive[i].ignoreCell == false)
        {
            cellsAlive[i].ignoreCell = true;
            grid.ResetGridSpace(cellsAlive[i].cellPosition);
        }
    }
}

#pragma endregion

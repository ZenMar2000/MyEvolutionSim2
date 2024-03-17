#include <iostream>

#include "../Headers/SimulationHandler.hpp"

#pragma region "Constructors"
SimulationHandler::SimulationHandler()
{
    char *title = (char *)"MySim";
    grid = Grid(title, Util.WindowWidth, Util.WindowHeight, &Util, &cellsAlive);

    // TODO Link grid to window

    // TODO generate random cells

    // TODO Create simulation loop

    // TODO Start simulation loop

    // TODO Add option to edit simulation parameters

    // std::cout<< to_string(Util.GetDirection(1).x) << endl;
}

#pragma endregion

#pragma region "Public Functions"
void SimulationHandler::Run()
{
    isRunning = true;
    while (isRunning)
    {
        // Check if exit button pressed (escape button)
        CheckIfExitRequested();

        // Perform each cell action, depending on it's genome
        PerformCellActions();
        CleanUpDeactivatedCells();

        // refresh the grid with updated positions of the cells
        grid.RefreshGrid();
    }
}

void SimulationHandler::GenerateCell(Vector2 position, int direction)
{
    Cell newCell = Cell(5, position, &Util, direction, &grid, 100);
    cellsAlive.push_back(newCell);
}
#pragma endregion

#pragma region "Protected Functions"
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
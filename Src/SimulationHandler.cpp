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
    // TODO Add logic for spawning also Neuron Nodes

    vector<string> newGenome;
    vector<pair<NodeId, NodeId>> selectedNodes;
    Cell *selectedCell;

    // Instantiate new cell and set space in grid as occupied
    cellsAlive[vectorPosition] = Cell(Util.baseGenomeLength, position, &Util, direction, &grid, Util.StartingFood);
    selectedCell = &cellsAlive[vectorPosition];
    grid.SetGridSpace(selectedCell->cellPosition);

    // Generate Random Genome
    for (int repeat = 0; repeat < selectedCell->GetGenomeLength(); repeat++)
    {
        NodeId newInput;
        NodeId newLinked;
        bool continueLogic = true;

#pragma region "Get random input/action node combination"
        // 1) Spawn input node
        for (int i = 0; i < Util.GetNodeTypeListSize(TYPE_INPUT); i++)
        {
            newInput = Util.GetRandomNode(TYPE_INPUT);

            // 2) Spawn action node
            for (int j = 0; j < Util.GetNodeTypeListSize(TYPE_ACTION); j++)
            {
                newLinked = Util.GetRandomNode(TYPE_ACTION);

                // 3) If Input/action node combination already exists, pick another Action Node, else continue
                for (int x = 0; x < selectedNodes.size(); x++)
                {
                    if (selectedNodes[x].first == newInput && selectedNodes[x].second == newLinked)
                    {
                        continueLogic = false;
                        break;
                    }
                    else
                    {
                        continueLogic = true;
                    }
                }

                if (continueLogic == true)
                {
                    break;
                }
            }
            if (continueLogic == true)
            {
                break;
            }
        }

        if (continueLogic == true)
        {
            selectedNodes.push_back(pair<NodeId, NodeId>(newInput, newLinked));
        }
        else
        {
            throw std::runtime_error("Error while spawning new genome: no Input/Action nodes combination available. Consider decreasing genomeLength or implementing new nodes.");
        }

#pragma endregion
    }

    // Create each genome from nodes previously drafted
    for (int i = 0; i < selectedNodes.size(); i++)
    {
        bool invertedLogic = Util.GetRandomInt(0, 2);
        int linkWeight = Util.GetRandomInt(0, 8);
        int genomeWeight = Util.GetRandomInt(0, 8);

        newGenome.push_back(BuildSingleGenome(invertedLogic, linkWeight, genomeWeight, selectedNodes[i].first, selectedNodes[i].second));
    }

    // Load full genome to cell
    cellsAlive[vectorPosition].LoadCellGenome(newGenome);
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

string SimulationHandler::BuildSingleGenome(bool invertedLogic, int linkWeight, int genomeWeight, NodeId firstNode, NodeId secondNode)
{
    string singleGenome;

    // First hex value (inverted logic and linkWeight)
    string invLogic = to_string(invertedLogic);
    string lw = bitset<3>(linkWeight % 8).to_string();
    singleGenome = Util.bin_to_hex(invLogic + lw);

    // Second hex value (genomeWeight)
    string gw = bitset<4>(genomeWeight % 8).to_string();
    singleGenome += Util.bin_to_hex(gw);

    // Thirth and Fourth hex value (first nodeId)
    string binId = bitset<8>(firstNode).to_string();
    singleGenome += Util.bin_to_hex(binId);

    // Fifth and Sixth hex value (second nodeId)
    binId = bitset<8>(secondNode).to_string();
    singleGenome += Util.bin_to_hex(binId);

    return singleGenome;
}

#pragma endregion

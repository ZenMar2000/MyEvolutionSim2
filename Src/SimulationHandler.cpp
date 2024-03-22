#include <iostream>

#include "../Headers/SimulationHandler.hpp"

#pragma region "Constructors"
SimulationHandler::SimulationHandler(int maxCells, int maxFood, bool foodEnabled, bool foodRespawn)
{
    Vector2 spawnPos;
    winwidthUnit = Util.WindowWidth / Util.CellPixelsDimension;
    winheightUnit = Util.WindowHeight / Util.CellPixelsDimension;

    char *title = (char *)"MySim";

    dimensionalCheck = (winwidthUnit * winheightUnit) * 0.5;

    if (maxCells > dimensionalCheck)
    {
        throw std::logic_error("Error: maxCells specified in SimulationHandler constructor [" + to_string(maxCells) + "] is greater than maximum for this window resolution and CellPixelsDimension (it is equal to half of pixel resolution). Max cell available: [" + to_string(dimensionalCheck) + "]");
    }

    grid = Grid(title, Util.WindowWidth, Util.WindowHeight, &Util);
    Util.foodEnabled = foodEnabled;

    InstantiateCellVector(maxCells);

    for (int i = 0; i < maxCells; i++)
    {
        GenerateCell((DirectionsIndex)Util.GetRandomInt(0, 8), i);
    }

    InstantiateAllFood(maxCells, maxFood, dimensionalCheck, foodRespawn);
}

#pragma endregion

#pragma region "Public Functions"
void SimulationHandler::Run()
{
    isRunning = true;
    grid.AddCellsToGrid(cellsAlive);
    grid.AddFoodToGrid(foodAvailable);
    while (isRunning)
    {

        // Check if exit button pressed (escape button)
        CheckIfExitRequested();

        // Perform each cell action, depending on it's genome
        PerformCellActions();
        CleanUpDeactivatedCells();

        // refresh the graphical grid with updated positions of the cells
        grid.RefreshGrid(currentSimulationStep, currentGeneration, simulationCutOff);

        // if (currentSimulationStep > simulationCutOff && survivors.size() <= 0)
        // {
        //     SaveCurrentGeneration();
        // }

        if (cellsAliveCounter <= 0)
        {
            if (BeginNewGeneration() == false)
            {
                break;
            }
        }
        currentSimulationStep++;
    }
}

#pragma endregion

#pragma region "Protected Functions"

void SimulationHandler::SaveCurrentGeneration()
{
    // for (int i = 0; i < cellsAlive.size(); i++)
    // {
    //     if (cellsAlive[i].IsAlive())
    //     {
    //         survivors.push_back(cellsAlive[i]);
    //     }
    // }
}

bool SimulationHandler::BeginNewGeneration()
{
    if (survivors.size() <= 0)
    {
        cout << "Simulation ended. Unfortunately no cells survived with current parameters." << endl;
        return false;
    }
    cout << "Gen " << currentGeneration << " max steps: " << currentSimulationStep << endl;

    currentSimulationStep = 0;
    currentGeneration++;

    int maxSpawnedCells = survivors.size() * 2;
    if (maxSpawnedCells > dimensionalCheck)
    {
        maxSpawnedCells = dimensionalCheck;
        simulationCutOff += Util.cutoffIncrease;
    }
    else if (Util.cutoffDecreaseEnabled)
    {
        if (simulationCutOff > Util.baseCutOffValue)
        {
            simulationCutOff -= Util.cutoffDecrease;
            if (simulationCutOff < Util.baseCutOffValue)
            {
                simulationCutOff = Util.baseCutOffValue;
            }
        }
    }
    InstantiateCellVector(maxSpawnedCells);

    int currentSurvivorIndex = survivors.size() - 1;
    int mutationsHappened = 0;
    for (int i = 0; i < cellsAlive.size(); i += 2)
    {
        for (int j = 0; j < 2; j++)
        {
            vector<string> currentCellGenome = survivors[currentSurvivorIndex].GetCellGenome();
            Color currentCellColor = survivors[currentSurvivorIndex].GetCellColor();
            if (Util.GetRandomInt(0, 1500) == 0)
            {
                // Mutation happened
                mutationsHappened++;
                NodeId inNode = Util.GetRandomNode(TYPE_INPUT);
                NodeId actNode = Util.GetRandomNode(TYPE_ACTION);

                int mutatedNodeIndex = -1;
                for (int i = 0; i < currentCellGenome.size(); i++)
                {
                    if (inNode == stoi(currentCellGenome[i].substr(2, 2), 0, 16) && actNode == stoi(currentCellGenome[i].substr(3, 2), 0, 16))
                    {
                        mutatedNodeIndex = i;
                        break;
                    }
                }

                if (mutatedNodeIndex == -1)
                {
                    mutatedNodeIndex = Util.GetRandomInt(0, currentCellGenome.size());
                }

                bool invertedLogic = Util.GetRandomInt(0, 2);
                int linkWeight = Util.GetRandomInt(1, Util.maxLinkWeight + 1) % 8;
                int genomeWeight = Util.GetRandomInt(1, Util.maxGenomeWeight + 1) % 8;

                currentCellGenome[mutatedNodeIndex] = BuildSingleGenome(invertedLogic, linkWeight, genomeWeight, inNode, actNode);

                currentCellColor = Util.GetRandomColor();
            }

            GenerateCell((DirectionsIndex)Util.GetRandomInt(0, 8), i + j, currentCellGenome, currentCellColor);

            if (i == cellsAlive.size() - 1)
            {
                int sssss = 0;
            }
        }
        // GenerateCell((DirectionsIndex)Util.GetRandomInt(0, 8), i + 1, survivors[currentSurvivorIndex].GetCellGenome());
        currentSurvivorIndex--;
    }

    grid.AddCellsToGrid(cellsAlive);
    survivors.clear();

    // if (mutationsHappened > 0)
    // {
    //     cout << "    " << mutationsHappened << " mutation" << (mutationsHappened == 1 ?" ": "s ") << "happened!" << endl;
    // }
    return true;
}

void SimulationHandler::ChangeRandomBit(string &str)
{
    // random_device rd;
    // mt19937 gen(rd());
    // uniform_int_distribution<int> distribution(0, str.size() * 8 - 1);

    // int randomBitIndex = distribution(gen);
    // int charIndex = randomBitIndex / 8;
    // int bitOffset = randomBitIndex % 8;

    int charIndex = Util.GetRandomInt(0, 8);
    int bitOffset = Util.GetRandomInt(0, 8);

    str[charIndex] ^= (1 << bitOffset);
}

void SimulationHandler::InstantiateCellVector(int maxCells)
{
    cellsAlive.clear();

    for (int i = 0; i < maxCells; i++)
    {
        cellsAlive.push_back(Cell());
    }
}

void SimulationHandler::GenerateCell(DirectionsIndex direction, int vectorPosition)
{
    cellsAliveCounter++;
    // Get spawn position
    Vector2 spawnPos;
    do
    {
        spawnPos = Vector2(Util.GetRandomInt(0, winwidthUnit), Util.GetRandomInt(0, winheightUnit));
    } while (grid.CheckIfCellSpaceFree(spawnPos) == false);

    // TODO Add logic for spawning also Neuron Nodes

    vector<string> newGenome;
    vector<pair<NodeId, NodeId>> selectedNodes;
    Cell *selectedCell;

    // Instantiate new cell and set space in grid as occupied
    cellsAlive[vectorPosition] = Cell(Util.baseGenomeLength, spawnPos, &Util, direction, &grid, Util.StartingFood);
    selectedCell = &cellsAlive[vectorPosition];
    grid.SetCellGridSpace(selectedCell->cellPosition);

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
        int linkWeight = Util.GetRandomInt(1, Util.maxLinkWeight + 1) % 8;
        int genomeWeight = Util.GetRandomInt(1, Util.maxGenomeWeight + 1) % 8;

        newGenome.push_back(BuildSingleGenome(invertedLogic, linkWeight, genomeWeight, selectedNodes[i].first, selectedNodes[i].second));
    }

    // Load full genome to cell
    cellsAlive[vectorPosition].LoadCellGenome(newGenome);
}

void SimulationHandler::GenerateCell(DirectionsIndex direction, int vectorPosition, vector<string> genome, Color color)
{
    cellsAliveCounter++;
    // Get spawn position
    Vector2 spawnPos;
    do
    {
        spawnPos = Vector2(Util.GetRandomInt(0, winwidthUnit), Util.GetRandomInt(0, winheightUnit));
    } while (grid.CheckIfCellSpaceFree(spawnPos) == false);

    // TODO Add logic for spawning also Neuron Nodes
    Cell *selectedCell;

    // Instantiate new cell and set space in grid as occupied
    cellsAlive[vectorPosition] = Cell(Util.baseGenomeLength, spawnPos, &Util, direction, &grid, Util.StartingFood);
    selectedCell = &cellsAlive[vectorPosition];
    grid.SetCellGridSpace(selectedCell->cellPosition);

    // Load full genome to cell
    cellsAlive[vectorPosition].LoadCellGenome(genome);
    selectedCell->SetCellColor(color);
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
            grid.ResetCellGridSpace(cellsAlive[i].cellPosition);
            cellsAliveCounter--;

            if (currentSimulationStep > simulationCutOff)
            {
                survivors.push_back(cellsAlive[i]);
            }
        }
    }
}
void SimulationHandler::InstantiateAllFood(int maxCells, int maxFood, int dimensionalCheck, bool foodRespawn)
{
    int foodDimensionalCheck = (dimensionalCheck - maxCells) * 0.75;
    if (maxFood > foodDimensionalCheck)
    {
        throw std::logic_error("Error: maxFood specified [" + to_string(maxFood) + "] is greater than maximum for this window resolution and CellPixelsDimension. Max food available: [" + to_string(foodDimensionalCheck) + "]");
    }

    if (Util.foodEnabled)
    {
        Vector2 foodSpawnPos;
        for (int i = 0; i < maxFood; i++)
        {
            do
            {
                foodSpawnPos = Vector2(Util.GetRandomInt(0, winwidthUnit), Util.GetRandomInt(0, winheightUnit));
            } while (grid.CheckIfCellSpaceFree(foodSpawnPos) == false && grid.CheckIfFoodSpaceFree(foodSpawnPos) == false);

            grid.SetFoodGridSpace(foodSpawnPos);
            foodAvailable.push_back(FoodElement(foodSpawnPos, foodRespawn));
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

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

        // refresh the graphical grid with updated positions of the cells
        grid.RefreshGrid();
    }
}

void SimulationHandler::GenerateCell(Vector2 position, DirectionsIndex direction)
{
    Cell newCell = Cell(5, position, &Util, direction, &grid, 100);

    // TODO GENERATE RANDOM GENOME

    // TEST SINGLE GENOME, LINK INPUT_BLK to ACTION_MFW

    LoadSingleCellGenome("110D82", &newCell);

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

void SimulationHandler::LoadSingleCellGenome(string singleCellGenome, Cell *targetCell)
{
    string binGenome[4];
    // Inverted logic and link weight
    string test = singleCellGenome.substr(0,1);
    binGenome[0] = Util.hex_to_bin(singleCellGenome.substr(0,1));

    // Genome weight
    binGenome[1] = Util.hex_to_bin(singleCellGenome.substr(1,1));

    // current node id
    binGenome[2] = Util.hex_to_bin(singleCellGenome.substr(2,2));

    // child node id linked to current node
    binGenome[3] = Util.hex_to_bin(singleCellGenome.substr(4,2));

    NodeType newCurrentNodetype = Util.GetNodeType(binGenome[2]);
    Node newCurrentNode;

    NodeType newLinkedNodeType = Util.GetNodeType(binGenome[3]);
    Node newLinkedNode;

    SpecializeNode(&newCurrentNode, (NodeId)Util.bin_to_int(binGenome[2]), targetCell);
    SpecializeNode(&newLinkedNode, (NodeId)Util.bin_to_int(binGenome[3]), targetCell);

    newCurrentNode.AddLinkedNode(&newLinkedNode, Util.bin_to_int(binGenome[0].substr(1,3)));

    targetCell->GenomeArray[newCurrentNodetype].push_back(newCurrentNode);
    targetCell->GenomeArray[newLinkedNodeType].push_back(newLinkedNode);
}

void SimulationHandler::SpecializeNode(Node *nodeToSpecialize, NodeId nodeId, Cell *targetCell)
{
    NodeType type = Util.GetNodeType(nodeId);
    switch (type)
    {
    case TYPE_INPUT:
        nodeToSpecialize = new InputNode((NodeId)(nodeId), targetCell);
        break;

    case TYPE_NEURON:
        // nodeToSpecialize =  NeuronNode();
        break;

    case TYPE_ACTION:
        nodeToSpecialize = new ActionNode((NodeId)(nodeId), targetCell);

        break;

    default:
        throw std::logic_error("Error in SimulationHandler::LoadSingleCellGenome(). Only TYPE_INPUT and TYPE_NEURON nodes have linked child nodes. Current TYPE is instead " + type);
        break;
    }
}

#pragma endregion

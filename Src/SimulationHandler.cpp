#include <iostream>

#include "../Headers/SimulationHandler.hpp"

SimulationHandler::SimulationHandler()
{
    char* title = (char*)"MySim";
    grid = Grid(title, 800, 600, &Util);

    // TODO Instantiate Graph, and generate random cells

    // TODO Create simulation loop

    // TODO Start simulation loop

    // TODO Add option to edit simulation parameters

    // std::cout<< to_string(Util.GetDirection(1).x) << endl;
}

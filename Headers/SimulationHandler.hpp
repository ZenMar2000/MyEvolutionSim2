#ifndef SIMHANDLER_H
#define SIMHANDLER_H

#include "Cell/Cell.hpp"
#include "Grid/Grid.hpp"
#include "Utils.hpp"

class SimulationHandler
{
public:
    // Costructors
    SimulationHandler();
    Utils Util = Utils();

protected:
    Grid grid = Grid();
    // Utils utlt = Utils();
};

#endif
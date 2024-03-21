#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(200, 100, true, true);

    sim.Run();

    return 0;
}
#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(500, 100, true);

    sim.Run();

    return 0;
}
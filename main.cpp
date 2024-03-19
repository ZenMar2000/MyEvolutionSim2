#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(3, false);
    
    sim.Run();

    return 0;
}
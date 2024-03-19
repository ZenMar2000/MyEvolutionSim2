#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(2, false);
    // sim.GenerateCell(Vector2(70, 30), DIRECTION_W);
    
    sim.Run();

    return 0;
}
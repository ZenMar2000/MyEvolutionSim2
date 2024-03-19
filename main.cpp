#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(2);
    sim.GenerateCell(Vector2(70, 30), DIRECTION_E);
    // sim.GenerateCell(Vector2(70, 30), DIRECTION_W);
    
    sim.Run();

    return 0;
}
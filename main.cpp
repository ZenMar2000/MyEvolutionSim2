#include "Headers/SimulationHandler.hpp"
#include <bitset>
#include <stdio.h>

int main()
{
    SimulationHandler sim = SimulationHandler(2);
    sim.GenerateCell(Vector2(70, 30), DIRECTION_E);
    // sim.GenerateCell(Vector2(70, 30), DIRECTION_W);
    sim.Run();

    // std::string binary = std::bitset<3>(7).to_string(); // to binary
    // std::cout << binary << "\n";

    // unsigned long decimal = std::bitset<4>(binary).to_ulong();
    // std::cout << decimal << "\n";
    // return 0;

    // Vector2 vect(1,1);
    // vect.Print();

    // Cell cell1;
    // cell1.position = Vector2(1,1);

    // SDLWindow myWindow("My Sim", WindowWidth, WindowHeight);
    // SDL_SetRenderDrawColor(myWindow.renderer, 255, 0, 0, 255);

    // while (true)
    // {
    //    SDL_PollEvent(&myWindow.event);
    //     if(myWindow.event.type == SDL_QUIT){
    //        break;
    //    }
    // }

    // SDL_Quit();
    return 0;
}
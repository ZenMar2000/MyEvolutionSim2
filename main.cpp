#include "Headers/Vector2/Vector2.hpp"
#include "Headers/Window/SDLWindow.hpp"
#include "Headers/Cell/Cell.hpp"
#include "Src/Utils.cpp"

int main(){


    Vector2 vect(1,1);
    vect.Print();

    // Cell cell1;
    // cell1.position = Vector2(1,1);


    SDLWindow myWindow("My Sim", WindowWidth, WindowHeight);
    SDL_SetRenderDrawColor(myWindow.renderer, 255, 0, 0, 255);

    while (true)
    {
       SDL_PollEvent(&myWindow.event);
        if(myWindow.event.type == SDL_QUIT){
           break;
       }  
    }

    SDL_Quit();
    return 0;
}
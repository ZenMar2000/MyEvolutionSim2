#include <iostream>
#include <string>

#include "Headers/Vector2/Vector2.hpp"
#include "Headers/Window/SDLWindow.hpp"

using namespace std;

int main(){
    uint width = 800;
    uint height =600;

    Vector2 vect(1,1);
    vect.Print();

    SDLWindow myWindow("My Sim",width,height);
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
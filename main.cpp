#include <iostream>
#include <string>

#include "Headers/Vector2/Vector2.hpp"
#include "Headers/Window/SDLWindow.hpp"

 using namespace std;



int main(){
    Vector2 vect(1,1);
    vect.Print();

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        cout << SDL_GetError();
    }
    else
    {
     SDLWindow myWindow("New window");
     while (true)
     {
        SDL_Event event;
        SDL_PollEvent(&event);

        if(event.type == SDL_QUIT){
            break;
        }     
     }
    }

    SDL_Quit();
    return 0;

}
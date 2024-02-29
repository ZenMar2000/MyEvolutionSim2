#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "Headers/Vector2/Vector2.hpp"

 using namespace std;

class SDLWindow{
    SDL_Window* window;
    public:
    SDLWindow(const char* title): window(SDL_CreateWindow(title,0,0,800,600, SDL_WINDOW_SHOWN)){
    }

    ~SDLWindow(){
        SDL_DestroyWindow(window);
    }
};


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
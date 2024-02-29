#include <SDL2/SDL.h>
#include <iostream>
#include <string>

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
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        cout << SDL_GetError();
    }
    else
    {
     SDLWindow myWindow("New window");
     SDL_Delay(5000);   
    }

    SDL_Quit();
    return 0;

}
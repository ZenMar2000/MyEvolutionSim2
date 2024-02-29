#include "../../Headers/Window/SDLWindow.hpp"

//Constructors
SDLWindow::SDLWindow(const char* title, uint width, uint height): window(SDL_CreateWindow(title,0,0,width,height, SDL_WINDOW_SHOWN)){
    Init();
};

SDLWindow::~SDLWindow(){
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

void SDLWindow::Init(){
    {
        //Start window
        if(SDL_Init(SDL_INIT_VIDEO) != 0){
            cout << SDL_GetError();
            return;
        }
        
        //Open and initialize black window
        SDL_Surface* surface = SDL_GetWindowSurface(window);
        SDL_Surface* image = SDL_LoadBMP(NULL);
        
        SDL_BlitSurface(image, NULL, surface, NULL);

        SDL_free(image);
        SDL_UpdateWindowSurface(window);

        renderer = SDL_CreateRenderer(window,-1,0);
        
    }
}
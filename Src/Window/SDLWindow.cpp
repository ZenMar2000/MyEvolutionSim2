#include "../../Headers/Window/SDLWindow.hpp"

//Constructors
SDLWindow::SDLWindow(const char* title): window(SDL_CreateWindow(title,0,0,800,600, SDL_WINDOW_SHOWN)){};

SDLWindow::~SDLWindow(){
        SDL_DestroyWindow(window);
    }
#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <SDL2/SDL.h>

class SDLWindow{
    SDL_Window* window;

    public:
    //Constructors
    SDLWindow(const char* title);
    ~SDLWindow();
};

#endif
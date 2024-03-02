#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class SDLWindow
{

public:
    // Variables
    SDL_Window *window;
    SDL_Event event;
    SDL_Renderer *renderer;

    // Constructors
    SDLWindow(const char *title, uint width, uint height);
    ~SDLWindow();

protected:
    void Init();
};

#endif
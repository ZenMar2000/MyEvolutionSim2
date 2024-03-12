#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include "../Utils.hpp"

using namespace std;

class SDLWindow
{

public:
#pragma region "Constructors"
    SDLWindow();
    SDLWindow(const char *title, uint width, uint height);
    ~SDLWindow();
#pragma endregion

#pragma region "Public Functions"
    void ClearWindow();
    void DrawPixel(uint r, uint g, uint b, Vector2 position);
    void UpdateWindow();

#pragma endregion

protected:
#pragma region "Protected Variables"
    void Init(uint width, uint height);
    Utils *util;
    SDL_Window *window;
    SDL_Renderer *renderer;
#pragma endregion
};

#endif
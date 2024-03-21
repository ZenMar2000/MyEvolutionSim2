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
    void DrawPixel(Color cellColor, Vector2 position);
    void UpdateWindow();
    void UpdateWindowTitle(string title);
#pragma endregion

protected:
#pragma region "Protected Variables"
    Utils *util;
    SDL_Window *window;
    SDL_Renderer *renderer;

#pragma endregion

#pragma region "Protected functions"
    void Init(const char *title, uint width, uint height);
#pragma endregion
};

#endif
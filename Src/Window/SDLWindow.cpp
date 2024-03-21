#include "../../Headers/Window/SDLWindow.hpp"

#pragma region "Constructors"
SDLWindow::SDLWindow() : window(){};
SDLWindow::SDLWindow(const char *title, uint width, uint height) //: window(SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN))
{
    Init(title, width, height);
};

SDLWindow::~SDLWindow()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
#pragma endregion

#pragma region "Public Functions"
void SDLWindow::ClearWindow()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDLWindow::DrawPixel(Color cellColor, Vector2 position)
{
    SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
    SDL_RenderDrawPoint(renderer, position.x, position.y);
}

void SDLWindow::UpdateWindow()
{
    SDL_RenderPresent(renderer);
    SDL_Delay(util->UpdateDelay);
}

void SDLWindow::UpdateWindowTitle(string title)
{
    char c[title.size() + 1];
    title.copy(c, title.size() + 1);
    c[title.size()] = '\0';

    SDL_SetWindowTitle(window, c);
}
#pragma endregion

#pragma region "Protected functions"
void SDLWindow::Init(const char *title, uint width, uint height)
{
    {
        // Start window
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            cout << SDL_GetError();
            return;
        }
        // Initialize window and renderer
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        // set renderer dimension to 10
        SDL_RenderSetScale(renderer, util->CellPixelsDimension, util->CellPixelsDimension);

        // Set clear the window to all black
        ClearWindow();
    }

#pragma endregion
}
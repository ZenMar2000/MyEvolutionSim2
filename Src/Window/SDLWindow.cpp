#include "../../Headers/Window/SDLWindow.hpp"

#pragma region "Constructors"
SDLWindow::SDLWindow() : window(){};
SDLWindow::SDLWindow(const char *title, uint width, uint height) : window(SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN))
{
    Init(width, height);
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

void SDLWindow::DrawPixel(uint r, uint g, uint b, Vector2 position)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, position.x, position.y);
}

void SDLWindow::UpdateWindow()
{
    SDL_RenderPresent(renderer);
}
#pragma endregion

#pragma region "Protected functions"
void SDLWindow::Init(uint width, uint height)
{
    {
        // Start window
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            cout << SDL_GetError();
            return;
        }

        // Initialize window and renderer
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

        // set renderer dimension to 10
        SDL_RenderSetScale(renderer, 10, 10);

        // Set clear the window to all black
        ClearWindow();

        // Set renderer color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, 79, 0);
        // for (int i = 0; i < height - 1; i++)
        // {
        //     SDL_RenderDrawPoint(renderer, i, i);
        //     SDL_RenderPresent(renderer);
        //     SDL_Delay(100);

        // }
        UpdateWindow();
        SDL_Delay(1000);
    }
#pragma endregion
}
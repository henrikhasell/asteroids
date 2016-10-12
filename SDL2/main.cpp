#include <iostream>
#include <SDL2/SDL.h>

#define PROJECT_NAME "Asteroids"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main( int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        std::cout << "Initialised SDL2 successfully." << std::endl;

        SDL_Window *window = SDL_CreateWindow(PROJECT_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if(window != nullptr)
        {
            std::cout << "Created SDL2 window successfully." << std::endl;

            SDL_DestroyWindow(window);
        }

        SDL_Quit();
    }
    else
    {
        std::cerr << "Failed to initialise SDL2: " << SDL_GetError() << std::endl;
    }

    return 0;
}

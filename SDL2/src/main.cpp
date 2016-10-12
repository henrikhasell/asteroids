#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#define PROJECT_NAME "Asteroids"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        std::cout << "Successfully initialised SDL2." << std::endl;

        SDL_Window *window = SDL_CreateWindow(PROJECT_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL
        );

        if(window != nullptr)
        {
            std::cout << "Successfully created SDL2 window." << std::endl;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GLContext context = SDL_GL_CreateContext(window);

            if(context != nullptr)
            {
                std::cout << "Successfully created OpenGL context." << std::endl;

                glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

                bool finished = false;

                while(!finished)
                {
                    SDL_Event event;

                    while(SDL_PollEvent(&event) != 0)
                    {
                        if(event.type == SDL_QUIT)
                        {
                            finished = true;
                        }
                        else
                        {
                            // TODO: Add other events.
                        }

                        // Render scene:

                        glClear(GL_COLOR_BUFFER_BIT);

                        SDL_GL_SwapWindow(window);
                    }
                }

                SDL_GL_DeleteContext(context);
            }
            else
            {
                std::cerr << "Failed to create OpenGL context:" << SDL_GetError() << std::endl;
            }

            SDL_DestroyWindow(window);
        }
        else
        {
            std::cerr << "Failed to create SDL2 window:" << SDL_GetError() << std::endl;
        }

        SDL_Quit();
    }
    else
    {
        std::cerr << "Failed to initialise SDL2: " << SDL_GetError() << std::endl;
    }

    return 0;
}

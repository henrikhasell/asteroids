#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "utilities/shader.hpp"
#include "utilities/program.hpp"

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

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

            SDL_GLContext context = SDL_GL_CreateContext(window);

            if(context != nullptr)
            {
                std::cout << "Successfully created OpenGL context." << std::endl;

                GLenum glewResult = glewInit();

                if(glewResult == GLEW_OK)
                {
                    std::cout << "Successfully loaded OpenGL extensions." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to load OpenGL extensions: " << glewGetErrorString(glewResult) << std::endl;
                }

                // Setup OpenGL:

                GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                GLuint program = glCreateProgram();

                if(Shader::Load(vertexShader, "shaders/vertex.glsl") != true)
                {
                    std::cerr << "Failed to load vertex shader." << std::endl;
                }

                if(Shader::Load(fragmentShader, "shaders/fragment.glsl") != true)
                {
                    std::cerr << "Failed to load fragment shader." << std::endl;
                }

                if(Program::Link(program, vertexShader, fragmentShader) != true)
                {
                    std::cerr << "Failed to link shader." << std::endl;
                }

                glUseProgram(program);

                const GLfloat vertices[] = {
                     0.0f,  0.5f,
                     0.5f, -0.5f,
                    -0.5f, -0.5f
                };

                GLuint vertexbuffer;
                glGenBuffers(1, &vertexbuffer);
                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

                        SDL_GL_SwapWindow(window);
                    }

                    // Render scene:
                    glClear(GL_COLOR_BUFFER_BIT);
                    glEnableVertexAttribArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
                    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                    glDisableVertexAttribArray(0);

                    // Display the scene:
                    SDL_GL_SwapWindow(window);

                    // Avoid throttling the CPU:
                    SDL_Delay(100);
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

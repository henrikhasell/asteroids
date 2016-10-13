#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "utilities/shader.hpp"
#include "utilities/program.hpp"
#include "model.hpp"

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

                const glm::vec2 vertices[3] = {
                    {+0.0f, +0.5f},
                    {+0.5f, -0.5f},
                    {-0.5f, -0.5f}
                };


                const glm::vec2 asteroid_1_vertices[10] = {
                    { -0.258829f, -0.466654f }, { -0.026869f, -0.217373f },
                    {  0.229284f, -0.486908f }, {  0.473549f, -0.231049f },
                    {  0.343808f,  0.036211f }, {  0.468176f,  0.270399f },
                    {  0.116252f,  0.513091f }, { -0.292469f,  0.513091f },
                    { -0.526451f,  0.272889f }, { -0.526451f, -0.203697f }
                };

                const glm::vec2 asteroid_2_vertices[12] = {
                    {  0.093883f, -0.003426f }, {  0.463877f, -0.152118f }, {  0.473194f, -0.265410f },
                    {  0.112516f, -0.512724f }, { -0.262802f, -0.512724f }, { -0.174962f, -0.260859f },
                    { -0.499283f, -0.260859f }, { -0.499283f,  0.130093f }, { -0.255886f,  0.479549f },
                    {  0.126392f,  0.356185f }, {  0.241383f,  0.487276f }, {  0.500717f,  0.231932f }
                };

                const glm::vec2 asteroid_3_vertices[12] = {
                    {  0.006423f, -0.327354f }, { -0.230594f, -0.457312f }, { -0.497797f, -0.197306f },
                    { -0.345536f,  0.041065f }, { -0.497575f,  0.282259f }, { -0.230955f,  0.533400f },
                    { -0.111968f,  0.396640f }, {  0.229570f,  0.525940f }, {  0.491186f,  0.142602f },
                    {  0.253211f, -0.073727f }, {  0.502203f, -0.212973f }, {  0.255415f, -0.466600f }
                };

                const glm::vec2 asteroid_4_vertices[12] = {
                    {  0.004242f,  0.128464f }, {  0.004242f,  0.479359f }, {  0.233801f,  0.479359f },
                    {  0.494881f,  0.128464f }, {  0.494881f, -0.197267f }, {  0.233801f, -0.520641f },
                    {  0.004242f, -0.520641f }, { -0.085344f, -0.520641f }, { -0.474404f, -0.169746f },
                    { -0.269635f, -0.033223f }, { -0.505119f,  0.138784f }, { -0.269635f,  0.469039f }
                };

                const glm::vec2 space_ship_vertices[4] = {
                    {-0.50f,  0.50f },
                    { 0.00f, -0.50f },
                    { 0.50f,  0.50f },
                    { 0.00f,  0.25f }
                };


                Model modelArray[] = {
                    {asteroid_1_vertices, 10},
                    {asteroid_2_vertices, 12},
                    {asteroid_3_vertices, 12},
                    {asteroid_4_vertices, 12},
                    {space_ship_vertices, 4}
                };

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
                    modelArray[4].draw();

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

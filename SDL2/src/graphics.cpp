#include "graphics.hpp"
#include "utilities/program.hpp"
#include "utilities/shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <GL/glew.h>
#include <iostream>

Graphics::Graphics()
{
    // Initialise the projection matrix:
    projectionMatrix = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);

    // Create vertex shader:
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Create fragment shader:
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Create program object:
    program = glCreateProgram();
}

Graphics::~Graphics()
{
    // Delete vertex shader:
    glDeleteShader(vertexShader);
    // Delete fragment shader:
    glDeleteShader(fragmentShader);
    // Delete program object:
    glDeleteProgram(program);
}

bool Graphics::link(const char vertex[], const char fragment[])
{
    if(Shader::Load(vertexShader, vertex) == true)
    {
        if(Shader::Load(fragmentShader, fragment) == true)
        {
            if(Program::Link(program, vertexShader, fragmentShader) == true)
            {
                // Use the newly linked program:
                glUseProgram(program);

                // Get the projection matrix uniform location from OpenGL:
                projectionUniform = glGetUniformLocation(program, "projectionMatrix");
                // Get the model matrix uniform location from OpenGL:
                modelUniform = glGetUniformLocation(program, "modelMatrix");
                // Get the view matrix uniform location from OpenGL:
                viewUniform = glGetUniformLocation(program, "viewMatrix");

                // Upload the projection matrix:
                glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
                // Upload the model matrix:
                glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);
                // Upload the view matrix:
                glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &viewMatrix[0][0]);

                return true;
            }
            else
            {
                std::cerr << "Failed to link shader program." << std::endl;
            }
        }
        else
        {
            std::cerr << "Failed to load fragment shader." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to load vertex shader." << std::endl;
    }

    return false;
}

void Graphics::draw(Model &model, const glm::vec2 &position, float scale, float rotation)
{
    glm::mat4x4 modelMatrix;

    modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, 1.0f));

    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, &modelMatrix[0][0]);

    model.draw();
}

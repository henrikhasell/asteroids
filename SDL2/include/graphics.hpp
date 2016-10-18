#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "model.hpp"
#include <glm/mat4x4.hpp>

class Graphics
{
public:
    Graphics();
    ~Graphics();
    bool link(const char vertex[], const char fragment[]);
    void draw(const Model &model, const glm::vec2 &position, float scale, float rotation);
protected:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;

    glm::mat4x4 projectionMatrix;
    glm::mat4x4 modelMatrix;
    glm::mat4x4 viewMatrix;

    GLint projectionUniform;
    GLint modelUniform;
    GLint viewUniform;
};

#endif /* GRAPHICS_HPP */

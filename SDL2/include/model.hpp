#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <cstddef>

class Model
{
public:
    Model(const glm::vec2 vertices[], GLsizei length);
    void draw();
private:
    GLuint vertexBuffer;
    GLsizei length;
};

#endif /* MODEL_HPP */

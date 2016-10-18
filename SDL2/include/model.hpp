#ifndef MODEL_HPP
#define MODEL_HPP

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <cstddef>

class Model
{
public:
    Model(GLenum mode, GLenum usage);
    void setVertices(const glm::vec2 vertices[], GLsizei length);
    void draw() const;
private:
    const GLenum mode;
    const GLenum usage;

    GLuint vertexBuffer;
    GLsizei length;
};

#endif /* MODEL_HPP */

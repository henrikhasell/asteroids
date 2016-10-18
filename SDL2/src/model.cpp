#include "model.hpp"

Model::Model(GLenum mode, GLenum usage) :
    mode(mode),
    usage(usage),
    length(0)
{
    glGenBuffers(1, &vertexBuffer);
}

void Model::setVertices(const glm::vec2 vertices[], GLsizei length)
{
    // Upload the new vertices to OpenGL:
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * length, vertices, usage);
    // Update the length:
    this->length = length;
}

void Model::draw() const
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(mode, 0, length);
    glDisableVertexAttribArray(0);
}

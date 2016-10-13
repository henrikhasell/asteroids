#include "model.hpp"

Model::Model(const glm::vec2 vertices[], GLsizei length) : length(length)
{
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * length, vertices, GL_STATIC_DRAW);
}

void Model::draw()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINE_LOOP, 0, length);
    glDisableVertexAttribArray(0);
}

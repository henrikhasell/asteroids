#include "utilities/program.hpp"

bool Program::Link(GLint program, GLint vertexShader, GLint fragmentShader)
{
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    return Program::Link(program);
}

bool Program::Link(GLint program)
{
    glLinkProgram(program);

    GLint result;

    glGetProgramiv(program, GL_LINK_STATUS, &result);

    return result == GL_TRUE;
}

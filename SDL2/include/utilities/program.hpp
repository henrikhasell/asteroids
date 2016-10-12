#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GL/glew.h>

namespace Program
{
    bool Link(GLint program, GLint vertexShader, GLint fragmentShader);
    bool Link(GLint program);
}

#endif /* PROGRAM_HPP */

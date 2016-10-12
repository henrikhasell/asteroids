#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>

namespace Shader
{
    bool Load(GLint shader, const char file[]);

    bool Compile(GLint shader, std::string &source);

    bool CompileStatus(GLint shader);

    std::string GetLog(GLint shader);
}

#endif /* SHADER_HPP */

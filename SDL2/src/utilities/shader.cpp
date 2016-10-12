#include "utilities/shader.hpp"
#include <fstream>

bool Shader::Load(GLint shader, const char file[])
{
    std::ifstream fileStream(file);

    if(fileStream.is_open() == true)
    {
        std::string shaderSource;

        while(fileStream.eof() != true)
        {
            std::string line;

            std::getline(fileStream, line);

            shaderSource += line + "\n";
        }

        return Shader::Compile(shader, shaderSource);
    }

    return false;
}


bool Shader::Compile(GLint shader, std::string &source)
{
    const GLchar *data = source.data();

    glShaderSource(shader, 1, &data, nullptr);

    glCompileShader(shader);

    return Shader::CompileStatus(shader);
}

bool Shader::CompileStatus(GLint shader)
{
    GLint result;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    return result == GL_TRUE;
}

std::string Shader::GetLog(GLint shader)
{
    return std::string();
}


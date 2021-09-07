//
// Created by NePutin on 9/7/2021.
//

#include <fstream>
#include <sstream>
#include "Shader.h"
#include <glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "ConsoleLog.h"
constexpr auto ENUM_TO_GL(palka::Shader::Type t)
{
    switch (t)
    {
        case palka::Shader::FRAGMENT:
            return GL_FRAGMENT_SHADER;
            break;
        case palka::Shader::VERTEX:
            return GL_VERTEX_SHADER;
            break;
    }
}

void palka::Shader::load(std::string_view file_name)
{
    std::ifstream file(file_name.data());
    if(file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        source = buffer.str();
    }
    file.close();
    compile();
}

void palka::Shader::compile()
{
    GLuint shader = glCreateShader(ENUM_TO_GL(type));
    const GLchar *src = (const GLchar *)source.c_str();
    glShaderSource(shader, 1, &src, 0);
    glCompileShader(shader);
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint logLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        if( logLen > 0 ) {
            std::string log(logLen, ' ');
            GLsizei written;
            glGetShaderInfoLog(shader, logLen, &written, &log[0]);
            Console::AppLog::addLog(log, Console::error);
        }
    }
    shaderID = glCreateProgram();
    glAttachShader(shaderID, shader);
    glLinkProgram(shaderID);
    GLint isLinked = 0;
    glGetProgramiv(shaderID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::string log(maxLength, ' ');
        glGetProgramInfoLog(shaderID, maxLength, &maxLength, &log[0]);
        Console::AppLog::addLog(log, Console::error);
        glDeleteProgram(shaderID);
        glDeleteShader(shader);
        return;
    }
    glDetachShader(shaderID, shader);
}

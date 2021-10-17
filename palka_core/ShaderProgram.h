//
// Created by NePutin on 9/28/2021.
//

#ifndef PALKA_SHADERPROGRAM_H
#define PALKA_SHADERPROGRAM_H

#include "Shader.h"
#include "ConsoleLog.h"
#include <glad/gl.h>

namespace palka
{
    class ShaderProgram
    {
    public:
        ShaderProgram(bool create = false)
        {
            if (create) createProgram();
        }

        void addShader(const Shader& shader)
        {
            glAttachShader(shaderProgramID, shader.getId());
        }

        void createProgram()
        {
            shaderProgramID = glCreateProgram();
        }

        void linkProgram()
        {
            glLinkProgram(shaderProgramID);
            isLinked = 0;
            glGetProgramiv(shaderProgramID, GL_LINK_STATUS, (int*) &isLinked);
            if (isLinked == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &maxLength);
                std::string log(maxLength, ' ');
                glGetProgramInfoLog(shaderProgramID, maxLength, &maxLength, &log[0]);
                Console::AppLog::addLog(log, Console::error);
                log.insert(0, "\n");
                glDeleteProgram(shaderProgramID);
                return;
            }
        }

        void deleteProgram()
        {
            if (!isLinked)
                return;
            glDeleteProgram(shaderProgramID);
            isLinked = 0;
        }

        ~ShaderProgram()
        {
            deleteProgram();
        }

    private:
        unsigned int shaderProgramID;
        GLint isLinked = 0;
    };
}

#endif //PALKA_SHADERPROGRAM_H

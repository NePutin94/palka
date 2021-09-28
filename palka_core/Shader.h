//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_SHADER_H
#define PALKA_SHADER_H

#include <string>
#include "Vec2.h"
#include "Transform.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace palka
{
    class Shader
    {
    public:
        enum Type
        {
            FRAGMENT,
            VERTEX,
            GEOMETRY
        };

        Shader(Type t = Type::FRAGMENT) : type(t)
        {}

        void load(std::string_view file_name);

        void loadVF(std::string_view file_name_fragment, std::string_view file_name_vertex);

        void setValue(std::string_view name, float value);

        void setValue(std::string_view name, int value)
        {}

        void setValue(std::string_view name, Transform t)
        {
            GLint loc = glGetUniformLocation((GLuint) shaderID, name.data());
            if (loc != -1)
            {
                glUniformMatrix4fv(loc, 1, GL_FALSE, t.getMatrix());
            }
        }

        void setValue(std::string_view name, glm::mat4 t)
        {
            GLint loc = glGetUniformLocation((GLuint) shaderID, name.data());
            if (loc != -1)
            {
                glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(t));
            }
        }

        void UseUbo() //need to do this using a static method or move it to a separate entity
        {
            unsigned int uboIndex = glGetUniformBlockIndex(shaderID, "matrixBuffer");
            glUniformBlockBinding(shaderID, uboIndex, 0);
            glGenBuffers(1, &UBO);
            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(float[16]) * 3, NULL, GL_STREAM_DRAW); //two float 4x4 matrices
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        void updateUBO(float* data, int L, int R)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
            glBufferSubData(GL_UNIFORM_BUFFER, L, R, data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }

        unsigned int getId()
        {
            return shaderID;
        }

    private:
        unsigned int shaderID;
        std::string source;
        Type type;
        unsigned int UBO;
        void compile();

        void setValue(std::string_view name, Vec2f value);
    };
}

#endif //PALKA_SHADER_H

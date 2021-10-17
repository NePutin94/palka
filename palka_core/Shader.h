//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_SHADER_H
#define PALKA_SHADER_H

#include <string>
#include "Vec2.h"
#include "Transform.h"
#include "UniformBuffer.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include "ConsoleLog.h"


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
                case palka::Shader::GEOMETRY:
                    return GL_GEOMETRY_SHADER;
                    break;
            }
            return -1;
        }

        void load(std::string_view file_name);

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
//
//        void UseUbo() //need to do this using a static method or move it to a separate entity
//        {
//            unsigned int uboIndex = glGetUniformBlockIndex(shaderID, "matrixBuffer");
//            glUniformBlockBinding(shaderID, uboIndex, 0);
//            ubo.create(sizeof(float[16]) * 3);
//            ubo.bindToPoint(0);
//
//            //ubo.bindToPoint(0);
////            unsigned int uboIndex = glGetUniformBlockIndex(shaderID, "matrixBuffer");
////            glUniformBlockBinding(shaderID, uboIndex, 0);
////            glGenBuffers(1, &UBO);
////            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
////            glBufferData(GL_UNIFORM_BUFFER, sizeof(float[16]) * 3, NULL, GL_STREAM_DRAW); //two float 4x4 matrices
////            glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
////            glBindBuffer(GL_UNIFORM_BUFFER, 0);
//        }
        void updateUBO(float* data, int L, int R)
        {
            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
            glBufferSubData(GL_UNIFORM_BUFFER, L, R, data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
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

//        void updateUBO(float* data, int L, int R)
//        {
//           //ubo.set(data, L, R);
//            ubo.setData(data, R, L);
////            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
////            glBufferSubData(GL_UNIFORM_BUFFER, L, R, data);
////            glBindBuffer(GL_UNIFORM_BUFFER, 0);
//        }
        void loadVF(std::string_view file_name_fragment, std::string_view file_name_vertex);
        unsigned int getId() const
        {
            return shaderID;
        }

    private:
       // UniformBuffer ubo;
        unsigned int shaderID;
        std::string source;
        Type type;
        unsigned int UBO;

        void compile();

        void setValue(std::string_view name, Vec2f value);
    };
}

#endif //PALKA_SHADER_H

//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_SHADER_H
#define PALKA_SHADER_H

#include <string>
#include "Vec2.h"

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
        unsigned int getId()
        {
            return shaderID;
        }
    private:
        unsigned int shaderID;
        std::string source;
        Type type;

        void compile();

        void setValue(std::string_view name, Vec2f value);
    };
}

#endif //PALKA_SHADER_H

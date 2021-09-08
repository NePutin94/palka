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

        void load(std::string_view file_name);

        void setValue(std::string_view name, float value);

        void setValue(std::string_view name, int value)
        {

        }
        unsigned int shaderID;
    private:
        std::string source;
        Type type = Type::FRAGMENT;

        void compile();




        void setValue(std::string_view name, Vec2f value);
    };
}

#endif //PALKA_SHADER_H

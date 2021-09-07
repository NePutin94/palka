//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_SHADER_H
#define PALKA_SHADER_H

#include <string>

namespace palka
{
    class Shader
    {
    public:
        enum Type
        {
            FRAGMENT,
            VERTEX
        };

        void load(std::string_view file_name);
 unsigned int shaderID;
    private:

        std::string source;
        Type type = Type::FRAGMENT;
        void compile();
    };
}

#endif //PALKA_SHADER_H

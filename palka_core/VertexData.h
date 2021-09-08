//
// Created by NePutin on 9/8/2021.
//

#ifndef PALKA_VERTEXDATA_H
#define PALKA_VERTEXDATA_H

#include <GL/gl.h>
#include "Vec2.h"
#include "Color.h"

namespace palka
{
    struct Vertex
    {
        Vec2f pos;
        Color color;
        Vec2f texCoord;
    };

    class VertArray
    {
    public:
        enum Type : short
        {
            Quads = 0,
            Lines,
            Line_Strip,
            Triangles,
            Triangle_Strip,
            Triangle_Fan
        };

        static constexpr GLenum type_to_gl(Type t)
        {
            constexpr GLenum enum_array[] = {GL_QUADS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN};
            return enum_array[t];
        }

        VertArray(Type t) : type(t)
        {}


        void add(const Vertex& vert)
        {
            vertecies.push_back(vert);
        }

        void add(Vertex&& vert)
        {
            vertecies.emplace_back(std::move(vert));
        }

        Vertex& operator[](std::size_t i)
        {
            return vertecies[i];
        }

        auto getType()
        {
            return type;
        }

    private:
        std::vector<Vertex> vertecies;
        Type type;
    };
}
#endif //PALKA_VERTEXDATA_H

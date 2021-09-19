//
// Created by NePutin on 9/8/2021.
//

#ifndef PALKA_VERTEXDATA_H
#define PALKA_VERTEXDATA_H

#include <GL/gl.h>
#include "Vec2.h"
#include "Color.h"

#ifdef REFLECTION_CORE
#include <rttr/type>
#include <rttr/registration_friend>
#endif

namespace palka
{
    class Vertex
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
#endif
    public:
        Vec2f pos;
        Color color;
        Vec2f texCoord;
        Vertex() {}
        Vertex(Vec2f pos, Color color, Vec2f texPos = {}) : pos(pos), color(color), texCoord(texPos)
        {}
        Vertex(Vec2f pos, Vec2f texPos) : pos(pos), color(Color::White()), texCoord(texPos)
        {}
        Vertex(Vec2f pos) : pos(pos), color(Color::White())
        {}
    };

    class VertArray
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
#endif
    public:
        enum Type : short
        {
            Quads = 0,
            Lines,
            Line_Strip,
            Line_Loop,
            Triangles,
            Triangle_Strip,
            Triangle_Fan,
            Points,
            Polygon
        };

        static constexpr GLenum type_to_gl(Type t)
        {
            constexpr GLenum enum_array[] = {GL_QUADS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_POINTS, GL_POLYGON};
            return enum_array[t];
        }

        VertArray() = default;

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

        auto begin()
        {
            return vertecies.begin();
        }

        auto end()
        {
            return vertecies.end();
        }

        auto getSize()
        {
            return vertecies.size();
        }

    private:
        std::vector<Vertex> vertecies;
        Type type;
    };
}
#endif //PALKA_VERTEXDATA_H

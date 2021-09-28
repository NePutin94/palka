//
// Created by NePutin on 9/8/2021.
//

#ifndef PALKA_VERTEXDATA_H
#define PALKA_VERTEXDATA_H

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
        Vec3f pos;
        Color color;
        Vec3f texCoord;
        Vertex() {}
        Vertex(Vec2f pos, Color color, Vec2f texPos = {}) : pos({pos.x,pos.y,1.0}), color(color), texCoord({texPos.x,texPos.y,0})
        {}
        Vertex(Vec2f pos, Vec2f texPos) : pos({pos.x,pos.y,1.0}), color(Color::White()), texCoord({texPos.x,texPos.y,0})
        {}
        Vertex(Vec2f pos) : pos({pos.x,pos.y,1.0}), color(Color::White())
        {}
        Vertex(Vec3f pos) : pos(pos), color(Color::White())
        {}
        Vertex(Vec3f pos,Color color) : pos(pos), color(color)
        {}
    };
//    class Vertex
//    {
//#ifdef REFLECTION_CORE
//    RTTR_ENABLE()
//
//        RTTR_REGISTRATION_FRIEND
//#endif
//    public:
//        Vec3f pos;
//        Color color;
//        Vec3f texCoord;
//
//        Vertex()
//        {}
//
//        Vertex(float x, float y, float z) : pos({x, y, z})
//        {}
//
//        Vertex(Vec2f pos, Color color, Vec2f texPos = {}) : pos({pos.x, pos.y, 0}), color(color), texCoord({texPos.x, texPos.y, 0})
//        {}
//
//        Vertex(Vec3f pos, Color color, Vec3f texPos = {}) : pos(pos), color(color), texCoord(texPos)
//        {}
//
//        Vertex(Vec2f pos, Vec2f texPos) : pos({pos.x, pos.y, 0}), color(Color::White()), texCoord({texPos.x, texPos.y, 0})
//        {}
//
//        Vertex(Vec3f pos, Vec3f texPos) : pos(pos), color(Color::White()), texCoord(texPos)
//        {}
//
//        Vertex(Vec3f pos) : pos(pos), color(Color::White())
//        {}
//
//        Vertex(Vec2f pos) : pos({pos.x, pos.y, 0}), color(Color::White())
//        {}
//    };

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
            Quad_Strip,
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
            constexpr GLenum enum_array[] = {GL_QUADS, GL_QUAD_STRIP, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES,
                                             GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_POINTS, GL_POLYGON};
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

//
// Created by neputin_94 on 11/14/2021.
//

#ifndef PALKA_VERTEXARRAY_H
#define PALKA_VERTEXARRAY_H

#include <type_traits>
#include "Vec2.h"
#include "Color.h"
#include "VertexArrayObject.h"


namespace palka
{
    template<typename T>
    concept VertexValue = std::is_base_of<T, Vec3f>::value ||
                          std::is_base_of<T, Color>::value ||
                          std::is_base_of<T, Vec2f>::value;

    class VertexArray
    {
    public:
        std::vector<Vec3f> coords;
        std::vector<Color> vertex_color;
        std::vector<Vec2f> texture_coords;
        std::vector<Vec3f> normals;
        VertexArrayObject vao;
        VertexBufferObject vbo;

    public:
        VertexArray() = default;

        enum type
        {
            COORD = 0,
            TEX_COORD,
            NORMALS,
            VERT_COLOR
        };

        template<type t, class... Args>
        void addRaw(Args&& ... args)
        {
            if constexpr (t == type::VERT_COLOR)
                vertex_color.emplace_back(std::forward<Args>(args)...);
            if constexpr (t == type::COORD)
                coords.emplace_back(std::forward<Args>(args)...);
            if constexpr (t == type::NORMALS)
                normals.emplace_back(std::forward<Args>(args)...);
            if constexpr (t == type::TEX_COORD)
                texture_coords.emplace_back(std::forward<Args>(args)...);
        }

        template<type typ, class T>
        void setData(std::vector<T> data)
        {
            if constexpr (typ == type::VERT_COLOR)
                vertex_color = data;
            if constexpr (typ == type::COORD)
                coords = data;
            if constexpr (typ == type::NORMALS)
                normals = data;
            if constexpr (typ == type::TEX_COORD)
                texture_coords = data;
        }

        void pushToBuffer(bool stash)
        {

        }

        void createVAO(VertexArrayObject& vao, VertexBufferObject& vbo)
        {

            //vbo_coords, vbo_normals, vbo_vert_color, vbo_tex_coords
            vbo.create(coords.size() * sizeof(Vec3f) + normals.size() * sizeof(Vec3f));
//            vbo_coords.create(coords.size());
//            vbo_normals.create(normals.size());
//            vbo_vert_color.create(vertex_color.size());
//            vbo_tex_coords.create(texture_coords.size());

            vbo.setData(coords.size() * sizeof(Vec3f), &coords[0].x);
            vbo.setData(sizeof(Vec3f) * normals.size(), &normals[0].x, coords.size() * sizeof(Vec3f));
            vbo.setData(sizeof(Color) * vertex_color.size(), &vertex_color[0].r, coords.size() * sizeof(Vec3f) + sizeof(Vec3f) * normals.size());
            vbo.setData(sizeof(Vec2f) * texture_coords.size(), &texture_coords[0].x, coords.size() * sizeof(Vec3f) +
                                                                                     sizeof(Vec3f) * normals.size() + sizeof(Color) * vertex_color.size());

//            vbo_coords.setData(sizeof(Vec3f) * coords.size(), &coords[0].x);
//            vbo_normals.setData(sizeof(Vec3f) * normals.size(), &normals[0].x);
//            vbo_vert_color.setData(sizeof(Color) * vertex_color.size(), &vertex_color[0].r);
//            vbo_tex_coords.setData(sizeof(Vec2f) * texture_coords.size(), &texture_coords[0].x);

            vao.bind();
//            vao.setPointer_u(vbo_coords, 0, 3, GL_FLOAT, sizeof(Vec3f), 0);
//            vao.setPointer_u(vbo_vert_color, 1, 3, GL_FLOAT, sizeof(Color), 0);
//            vao.setPointer_u(vbo_tex_coords, 2, 3, GL_FLOAT, sizeof(Vec2f), 0);
//            vao.setPointer_u(vbo_normals, 3, 3, GL_FLOAT, sizeof(Vec3f), 0);
            vao.setPointer_u(vbo, 0, 3, GL_FLOAT, sizeof(Vec3f), 0);
            vao.setPointer_u(vbo, 1, 3, GL_FLOAT, sizeof(Color), 0);
            vao.setPointer_u(vbo, 2, 3, GL_FLOAT, sizeof(Vec2f), 0);
            vao.setPointer_u(vbo, 3, 3, GL_FLOAT, sizeof(Vec3f), 0);
            vao.unbind();
        }
    };
}
#endif //PALKA_VERTEXARRAY_H

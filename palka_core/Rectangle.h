//
// Created by NePutin on 9/18/2021.
//

#ifndef PALKA_RECTANGLE_H
#define PALKA_RECTANGLE_H

#include "Drawable.h"
#include "BlendMode.h"
#include "Rect.h"
#include "TransformObject.h"
#include "VertexData.h"
#include "RenderContext.h"

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/wrapper_mapper.h>
#include <rttr/registration_friend>
#include "RawPtrWrapper.h"

#endif

namespace palka
{
    class Rectangle : public Drawable, public TransformObject
    {
#ifdef REFLECTION_CORE
    RTTR_ENABLE(TransformObject)

        RTTR_REGISTRATION_FRIEND
#endif

        void update()
        {
            bool del = false;

            VertArray vertices(VertArray::Points);
            vertices.add(Vec2f{rect.left, rect.top});
            vertices.add(Vec2f{rect.w, rect.top});
            vertices.add(Vec2f{rect.w, rect.h});
            vertices.add(Vec2f{rect.left, rect.h});
            int j = 0;
            for (int i = 0; i < 4; ++i)
            {
                Vec2f a = (i == 0) ? vertices[3].pos : vertices[i - 1].pos;
                Vec2f b = vertices[i].pos;
                Vec2f c = (i == 3) ? vertices[0].pos : vertices[i + 1].pos;

                Vec2f normal = (b - a).normalize();
                Vec2f normal2 = (b - c).normalize();

                float len = 1.f + (normal * normal2).lenght();
                Vec2f dir = (normal + normal2) / len;
                Vec2f t = b + dir * sz;
                //vertices2.add({b + normal * sz, Color{255, 0, 0}});
                //vertices2.add({b + normal2 * sz, Color{255, 0, 0}});
                outline[j++] = Vertex({b, Color{255, 0, 0}});
                outline[j++] = Vertex({b + dir * sz, Color{100, 200, 90}});
            }
            outline[j++] = outline[0];
            outline[j++] = outline[1];

//            vertex[0].pos = {rect.left - sz, rect.top - sz};
//            vertex[1].pos = {rect.w + sz, rect.top - sz};
//            vertex[2].pos = {rect.left, rect.top};
//            vertex[3].pos = {rect.w, rect.top};
//            vertex[4].pos = {rect.w, rect.top};
//            vertex[5].pos = {rect.w, rect.h};
//            vertex[6].pos = {rect.w + sz, rect.top - sz};
//            vertex[7].pos = {rect.w + sz, rect.h + sz};
//            vertex[8].pos = {rect.w + sz, rect.h + sz};
//            vertex[9].pos = {rect.left - sz, rect.h + sz};
//            vertex[10].pos = {rect.w, rect.h};
//            vertex[11].pos = {rect.left, rect.h};
//            vertex[12].pos = {rect.left, rect.h};
//            vertex[13].pos = {rect.left, rect.top};
//            vertex[14].pos = {rect.left - sz, rect.h + sz};
//            vertex[15].pos = {rect.left - sz, rect.top - sz};
        }

        void updateColor()
        {
//            for (auto& v: vertex)
//                v.color = color;
        }

    public:
        Rectangle(RectF rect, float sz = 2) : rect(rect), outline(VertArray::Triangle_Strip), sz(sz)
        {
            VertArray vertices(VertArray::Points);
            vertices.add(Vec2f{rect.left, rect.top});
            vertices.add(Vec2f{rect.w, rect.top});
            vertices.add(Vec2f{rect.w, rect.h});
            vertices.add(Vec2f{rect.left, rect.h});
            for (int i = 0; i < 4; ++i)
            {
                Vec2f a = (i == 0) ? vertices[3].pos : vertices[i - 1].pos;
                Vec2f b = vertices[i].pos;
                Vec2f c = (i == 3) ? vertices[0].pos : vertices[i + 1].pos;

                Vec2f normal = (b - a).normalize();
                Vec2f normal2 = (b - c).normalize();

                float len = 1.f + (normal * normal2).lenght();
                Vec2f dir = (normal + normal2) / len;
                Vec2f t = b + dir * sz;
                //vertices2.add({b + normal * sz, Color{255, 0, 0}});
                //vertices2.add({b + normal2 * sz, Color{255, 0, 0}});
                outline.add({b, Color{255, 0, 0}});
                outline.add({b + dir * sz, Color{100, 200, 90}});
            }
            outline.add(outline[0]);
            outline.add(outline[1]);

//            vertex.add(Vertex{{rect.left - sz, rect.top - sz}, color});
//            vertex.add(Vertex{{rect.w + sz, rect.top - sz}, color});
//            vertex.add(Vertex{{rect.left, rect.top}, color});
//            vertex.add(Vertex{{rect.w, rect.top}, color});
//            vertex.add(Vertex{{rect.w, rect.top}, color});
//            vertex.add(Vertex{{rect.w, rect.h}, color});
//            vertex.add(Vertex{{rect.w + sz, rect.top - sz}, color});
//            vertex.add(Vertex{{rect.w + sz, rect.h + sz}, color});
//            vertex.add(Vertex{{rect.w + sz, rect.h + sz}, color});
//            vertex.add(Vertex{{rect.left - sz, rect.h + sz}, color});
//            vertex.add(Vertex{{rect.w, rect.h}, color});
//            vertex.add(Vertex{{rect.left, rect.h}, color});
//            vertex.add(Vertex{{rect.left, rect.h}, color});
//            vertex.add(Vertex{{rect.left, rect.top}, color});
//            vertex.add(Vertex{{rect.left - sz, rect.h + sz}, color});
//            vertex.add(Vertex{{rect.left - sz, rect.top - sz}, color});
        }

        void draw(Renderer& win) const;

        void setColor(Color c)
        {
            color = c;
            updateColor();
        }

        Color getColor()
        {
            return color;
        }

        RectF getRect()
        {
            return rect;
        }

        void setRect(RectF rect)
        {
            this->rect = rect;
            update();
        }

        void setSize(float size)
        {
            sz = size;
            update();
        }

        float getSize()
        {
            return sz;
        }

    private:
        Vec2f center;
        float sz;
        RectF rect;
        Color color;
        VertArray outline;
    };
}

#endif //PALKA_RECTANGLE_H

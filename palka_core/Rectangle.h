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
            vertex[0].pos = {rect.left - sz, rect.top - sz};
            vertex[1].pos = {rect.w + sz, rect.top - sz};
            vertex[2].pos = {rect.left, rect.top};
            vertex[3].pos = {rect.w, rect.top};
            vertex[4].pos = {rect.w, rect.top};
            vertex[5].pos = {rect.w, rect.h};
            vertex[6].pos = {rect.w + sz, rect.top - sz};
            vertex[7].pos = {rect.w + sz, rect.h + sz};
            vertex[8].pos = {rect.w + sz, rect.h + sz};
            vertex[9].pos = {rect.left - sz, rect.h + sz};
            vertex[10].pos = {rect.w, rect.h};
            vertex[11].pos = {rect.left, rect.h};
            vertex[12].pos = {rect.left, rect.h};
            vertex[13].pos = {rect.left, rect.top};
            vertex[14].pos = {rect.left - sz, rect.h + sz};
            vertex[15].pos = {rect.left - sz, rect.top - sz};
        }

        void updateColor()
        {
            for (auto& v: vertex)
                v.color = color;
        }

    public:
        Rectangle(RectF rect, float sz = 2) : rect(rect), vertex(VertArray::Triangle_Strip), sz(sz)
        {
            vertex.add(Vertex{{rect.left - sz, rect.top - sz}, color});
            vertex.add(Vertex{{rect.w + sz, rect.top - sz}, color});
            vertex.add(Vertex{{rect.left, rect.top}, color});
            vertex.add(Vertex{{rect.w, rect.top}, color});
            vertex.add(Vertex{{rect.w, rect.top}, color});
            vertex.add(Vertex{{rect.w, rect.h}, color});
            vertex.add(Vertex{{rect.w + sz, rect.top - sz}, color});
            vertex.add(Vertex{{rect.w + sz, rect.h + sz}, color});
            vertex.add(Vertex{{rect.w + sz, rect.h + sz}, color});
            vertex.add(Vertex{{rect.left - sz, rect.h + sz}, color});
            vertex.add(Vertex{{rect.w, rect.h}, color});
            vertex.add(Vertex{{rect.left, rect.h}, color});
            vertex.add(Vertex{{rect.left, rect.h}, color});
            vertex.add(Vertex{{rect.left, rect.top}, color});
            vertex.add(Vertex{{rect.left - sz, rect.h + sz}, color});
            vertex.add(Vertex{{rect.left - sz, rect.top - sz}, color});
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
        float sz;
        RectF rect;
        Color color;
        VertArray vertex;
    };
}

#endif //PALKA_RECTANGLE_H

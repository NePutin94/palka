//
// Created by NePutin on 9/18/2021.
//

#ifndef PALKA_PRIMITIVE_H
#define PALKA_PRIMITIVE_H

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
    class Primitive : public Drawable, public TransformObject
    {
#ifdef REFLECTION_CORE
    RTTR_ENABLE(TransformObject)

        RTTR_REGISTRATION_FRIEND
#endif

        void update()
        {

            vertex[0] = Vertex{{0.f, 0.f}, color};
            vertex[1] = Vertex{{(float) rect.w, 0.f}, color};
            vertex[2] = Vertex{{(float) rect.w, (float) rect.h}, color};
            vertex[3] = Vertex{{-1.f, (float) rect.h}, color};
        }

    public:
        Primitive(RectF rect) : rect(rect), vertex(VertArray::Line_Lopp)
        {
            vertex.add(Vertex{{0.f, 0.f}, color});
            vertex.add(Vertex{{(float) rect.w, 0.f}, color});
            vertex.add(Vertex{{(float) rect.w, (float) rect.h}, color});
            vertex.add(Vertex{{-1.f, (float) rect.h}, color});
        }

        void draw(Renderer& win) const;

        void setColor(Color c)
        {
            color = c;
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

    private:
        RectF rect;
        Color color;
        VertArray vertex;
    };
}

#endif //PALKA_PRIMITIVE_H

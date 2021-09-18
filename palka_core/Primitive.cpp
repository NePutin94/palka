//
// Created by NePutin on 9/18/2021.
//

#include "Primitive.h"
#include "Renderer.h"

void palka::Primitive::draw(palka::Renderer& win) const
{
    RenderContext context;
    context.transform = getTransform();
    win.draw(vertex, context);
}

#ifdef REFLECTION_CORE

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Primitive>("Primitive")
            .constructor<palka::RectF>()
            .property("setRect", &palka::Primitive::getRect, &palka::Primitive::setRect)
            .property("color", &palka::Primitive::color);
}
#endif
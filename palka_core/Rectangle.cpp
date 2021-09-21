//
// Created by NePutin on 9/18/2021.
//

#include <glad/gl.h>
#include "Rectangle.h"
#include "Renderer.h"

void palka::Rectangle::draw(palka::Renderer& win) const
{
    RenderContext context;
    context.transform = getTransform();
    win.draw(outline, context);
}

#ifdef REFLECTION_CORE

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Rectangle>("Rectangle")
            .constructor<palka::RectF>()
            .property("setRect", &palka::Rectangle::getRect, &palka::Rectangle::setRect)
            .property("color", &palka::Rectangle::getColor, &palka::Rectangle::setColor)
            .property("corner size", &palka::Rectangle::getSize, &palka::Rectangle::setSize);
}
#endif
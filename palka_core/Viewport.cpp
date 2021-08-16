//
// Created by NePutin on 7/5/2021.
//

#include "Viewport.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Viewport>("Viewport")
            .constructor<palka::RectF>()
            .property("center", &palka::Viewport::getCenter, &palka::Viewport::setCenter)
            .property("scale", &palka::Viewport::getScale, &palka::Viewport::setScale);
}

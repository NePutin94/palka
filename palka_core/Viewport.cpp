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
            .property("center", &palka::Viewport::center)
            .property("rect", &palka::Viewport::rect)
            .property("size", &palka::Viewport::size)
            .property("t", &palka::Viewport::t)
            .property("rotation", &palka::Viewport::rotation)
            .property("needUpdate", &palka::Viewport::needUpdate);
}
//
// Created by NePutin on 6/23/2021.
//

#include "Vec2.h"
#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Vec2f>("Vec2f")
            .constructor<>()
            .property("x", &palka::Vec2f::x)
            .property("y", &palka::Vec2f::y);
}
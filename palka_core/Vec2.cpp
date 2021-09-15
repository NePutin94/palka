//
// Created by NePutin on 6/23/2021.
//

#include "Vec2.h"

#ifdef REFLECTION_CORE
#include <rttr/registration>
RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Vec2f>("Vec2f")
            .constructor<>()
            .property("x", &palka::Vec2f::x)
            .property("y", &palka::Vec2f::y);
    registration::class_<palka::Vec2i>("Vec2i")
            .constructor<>()
            .property("x", &palka::Vec2i::x)
            .property("y", &palka::Vec2i::y);
}
#endif


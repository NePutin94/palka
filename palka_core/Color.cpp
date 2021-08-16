//
// Created by NePutin on 8/15/2021.
//

#include "Color.h"
#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<palka::Color>("Color")
            .property("r", &palka::Color::r)
            .property("g", &palka::Color::g)
            .property("b", &palka::Color::b);
}


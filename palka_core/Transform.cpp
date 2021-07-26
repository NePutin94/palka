//
// Created by NePutin on 7/7/2021.
//

#include "Transform.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Transform>("Transform")
            .constructor<palka::Transform>()
            .property("matrix", &palka::Transform::matrix);
}
//
// Created by NePutin on 6/26/2021.
//

#include "Sprite.h"
#ifdef REFLECTION_CORE
#include <rttr/registration>
RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Sprite>("Sprite")
            .constructor<>()
            .property("t", &palka::Sprite::t)
            .property("src", &palka::Sprite::src);
}
#endif

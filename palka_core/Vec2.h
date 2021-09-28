//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_VEC2_H
#define PALKA_VEC2_H

#include "config.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cmath>
#include <string>

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/registration_friend>

#endif
namespace palka
{
    using Vec2f = glm::vec2;
    using Vec3f = glm::vec3;
    using Vec2i = glm::ivec2;
}
#endif //PALKA_VEC2_H

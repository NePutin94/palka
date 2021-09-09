//
// Created by NePutin on 8/15/2021.
//

#ifndef PALKA_COLOR_H
#define PALKA_COLOR_H
#include "config.h"

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/registration_friend>

#endif

namespace palka
{
    struct Color
    {
#ifdef REFLECTION_CORE
    RTTR_ENABLE()
#endif
    public:
        Color() = default;

        Color(unsigned char r, unsigned char g, unsigned char b) noexcept: r(r), g(g), b(b)
        {}

        unsigned char r = 0;
        unsigned char g = 0;
        unsigned char b = 0;
    };
}
#endif //PALKA_COLOR_H

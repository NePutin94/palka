//
// Created by NePutin on 8/15/2021.
//

#ifndef PALKA_COLOR_H
#define PALKA_COLOR_H

#include <rttr/registration>

namespace palka
{
    struct Color
    {
    RTTR_ENABLE()
    public:
        Color(int r, int g, int b) noexcept: r(r), g(g), b(b)
        {}

        unsigned int r = 0;
        unsigned int g = 0;
        unsigned int b = 0;
    };
}
#endif //PALKA_COLOR_H

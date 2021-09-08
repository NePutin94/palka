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
        Color(uint8_t r, uint8_t g, uint8_t b) noexcept: r(r), g(g), b(b)
        {}

        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
    };
}
#endif //PALKA_COLOR_H

//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_DRAWABLE_H
#define PALKA_DRAWABLE_H

#include <SDL_render.h>

namespace palka
{
    class Drawable
    {
    public:
        virtual ~Drawable()
        {}

        virtual void draw(SDL_Renderer* target) const = 0;
    };
}
#endif //PALKA_DRAWABLE_H

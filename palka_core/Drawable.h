//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_DRAWABLE_H
#define PALKA_DRAWABLE_H

#include <SDL_render.h>

namespace palka
{
    class Window;
    class Drawable
    {
    private:
        virtual void draw(Window& win) const = 0;

    public:
        virtual ~Drawable()
        {}

        friend class Window;
    };
}
#endif //PALKA_DRAWABLE_H

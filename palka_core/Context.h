//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_CONTEXT_H
#define PALKA_CONTEXT_H

#include <SDL.h>

namespace palka
{
    struct Context
    {
    private:
        static SDL_Renderer* context;
    public:
        static SDL_Renderer* GetContext()
        {
            return context;
        }

        static void SetContext(SDL_Renderer* c)
        {
            context = c;
        }
    };
}

#endif //PALKA_CONTEXT_H

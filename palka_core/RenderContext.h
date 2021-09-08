//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_RENDERCONTEXT_H
#define PALKA_RENDERCONTEXT_H

#include "Texture.h"

namespace palka
{
    class RenderContext
    {
    private:
        Texture* texture;
    public:
        RenderContext(){}
        RenderContext(Texture* tex) : texture(tex)
        {}
    };
}

#endif //PALKA_RENDERCONTEXT_H

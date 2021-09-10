//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_RENDERCONTEXT_H
#define PALKA_RENDERCONTEXT_H

#include "BlendMode.h"
#include "Texture.h"
#include "Transform.h"

namespace palka
{
    class RenderContext
    {
    public:
        Texture* texture;
        BlendMode blend;
        Transform transform;
    public:
        RenderContext()
        {}

        RenderContext(Texture* tex) : texture(tex)
        {}

        friend class Window;
    };
}

#endif //PALKA_RENDERCONTEXT_H

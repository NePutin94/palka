//
// Created by NePutin on 6/26/2021.
//

#ifndef PALKA_SPRITE_H
#define PALKA_SPRITE_H

#include <utility>
#include "Drawable.h"
#include "Texture.h"
#include "Rect.h"
#include "Matrix.h"
#include "Transform.h"
#include "TransformObject.h"

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/registration_friend>

#endif
namespace palka
{
    class Sprite : public Drawable, public TransformObject
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE(TransformObject)
        RTTR_REGISTRATION_FRIEND
#endif
    private:
        const Texture* txt;
        RectI src;
        SDL_RendererFlip flip_p = SDL_FLIP_NONE;
    public:

        Sprite() = default;

        Sprite(const Texture& tex);

        void setTexture(const Texture& tex, RectI rect = {});

        void setTextureRect(RectI rect);

        void setFlip(SDL_RendererFlip flip_p)
        { this->flip_p = flip_p; }

        SDL_RendererFlip getFlip()
        { return flip_p; }

        RectI getTextureRect() const;

        RectI getLocalRect() const;

        RectF getGlobalRect() const;

        void draw(SDL_Renderer* , SDL_FPoint viewPos) const override;

        friend class Window;
    };
}
#endif //PALKA_SPRITE_H

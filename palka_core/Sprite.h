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

#ifdef REFLECTION_CORE
#include <rttr/type>
#include <rttr/registration_friend>
#endif
namespace palka
{
    class Sprite : public Drawable
    {
    private:
        const Texture* txt;
        float scale;
        RectI src;
        Transform t;
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
#endif
    public:
        struct
        {
            Vec2i size;
            Vec2i pos;
            Vec2i center;
            Quad<int> TrueQuad;
            float rotation;

            void rotate(float angle)
            {
                rotation = angle;
                Vec2i center2 = {static_cast<int>(pos.x + size.x / 2.f), static_cast<int>(pos.y + size.y / 2.f)};
                center = center2;
                TrueQuad = getLocalRect().rotate(rotation, center2);
            }

            void setRect(RectI r)
            {
                pos = {r.left, r.top};
                size = {r.w, r.h};
            }

            [[nodiscard]] RectI getLocalRect() const
            {
                return RectI(pos.x, pos.y, size.x, size.y);
            }

            [[nodiscard]] RectI getGlobalRect() const
            {
                return {pos.x, pos.y, size.x + pos.x, pos.y + size.y};
            }
        } dst;

        Sprite() = default;

        Sprite(const Texture& tex, Vec2i size, Vec2i pos = {0, 0})
        {
            txt = &tex;
            dst.pos = pos;
            dst.size = size;
            dst.rotation = 0;
        }

        void setSize(Vec2i sz)
        {
            dst.size = sz;
        }

        void setRotation(float angle)
        {
            dst.rotate(angle);
        }

        void setTexture(const Texture& tex, RectI rect = {})
        {
            txt = &tex;
            setTextureRect(rect);
        }

        void setPosition(Vec2i pos)
        {
            dst.pos = pos;
        }

        void setTextureRect(RectI rect)
        {
            src = rect;
        }

        void draw(SDL_Renderer* r) const override
        {
            auto t = src.getRect();
            auto tt = dst.getLocalRect().getRect();
            SDL_RenderCopyEx(r, txt->getSdl(), &t, &tt, dst.rotation, NULL, SDL_FLIP_NONE);
        }
    };
}
#endif //PALKA_SPRITE_H

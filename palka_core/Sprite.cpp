//
// Created by NePutin on 6/26/2021.
//

#include "Sprite.h"
#include "Rect.h"

void palka::Sprite::setTexture(const Texture& tex, RectI rect)
{
    txt = &tex;
    setTextureRect(rect);
}

void palka::Sprite::setTextureRect(palka::RectI rect)
{
    src = rect;
    setCenter({src.w / 2.f, src.h / 2.f});
}

palka::RectI palka::Sprite::getTextureRect() const
{
    return src;
}

palka::RectI palka::Sprite::getLocalRect() const
{
    return RectI(0, 0, src.w, src.h);
}

palka::RectF palka::Sprite::getGlobalRect() const
{
    return RectF{getPosition().x, getPosition().y, (float) src.w * getScale().x, (float) src.h * getScale().y};
}

void palka::Sprite::draw(SDL_Renderer* r, SDL_FPoint viewPos) const
{
    assert(("Texture is empty", !(txt == nullptr)));
    auto srcRect = src.getRect();
    auto dstRect = getGlobalRect().getRectF();
    dstRect.x -= viewPos.x;
    dstRect.y -= viewPos.y;
    SDL_FPoint center = {getCenter().x, getCenter().y};
    SDL_RenderCopyExF(r, txt->getSdl(), &srcRect, &dstRect, getRotation(), &center, flip_p);
}

palka::Sprite::Sprite(const palka::Texture& tex)
{
    txt = &tex;
    auto sz = tex.getSize();
    setTextureRect({0, 0, sz.x, sz.y});
}

#ifdef REFLECTION_CORE

#include <rttr/registration>

RTTR_REGISTRATION
{
    registration::enumeration<SDL_RendererFlip>("SDL_RendererFlip")
            (
                    value("SDL_FLIP_VERTICAL", SDL_RendererFlip::SDL_FLIP_VERTICAL),
                    value("SDL_FLIP_HORIZONTAL", SDL_RendererFlip::SDL_FLIP_HORIZONTAL),
                    value("SDL_FLIP_NONE", SDL_RendererFlip::SDL_FLIP_NONE)
            );
    using namespace rttr;
    registration::class_<palka::Sprite>("Sprite")
            .constructor<>()
            .property("setRect", &palka::Sprite::getTextureRect, &palka::Sprite::setTextureRect)
            .property("flip", &palka::Sprite::getFlip, &palka::Sprite::setFlip)
            .property("src", &palka::Sprite::src);
}

#endif
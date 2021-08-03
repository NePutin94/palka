//
// Created by NePutin on 6/26/2021.
//

#include "Sprite.h"

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

auto palka::Sprite::getTextureRect()
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

void palka::Sprite::draw(SDL_Renderer* r) const
{
    auto srcRect = src.getRect();
    auto dstRect = getGlobalRect().getRectF();
    SDL_RenderCopyExF(r, txt->getSdl(), &srcRect, &dstRect, getRotation(), NULL, SDL_FLIP_NONE);
}

palka::Sprite::Sprite(const palka::Texture& tex)
{
    txt = &tex;
}

#ifdef REFLECTION_CORE
#include <rttr/registration>
RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Sprite>("Sprite")
            .constructor<>()
            .property("setRect", &palka::Sprite::getTextureRect, &palka::Sprite::setTextureRect)
            .property("src", &palka::Sprite::src);
}
#endif
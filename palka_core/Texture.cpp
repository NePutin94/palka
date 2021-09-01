//
// Created by NePutin on 6/23/2021.
//

#include "Texture.h"

palka::Texture& palka::Texture::operator=(palka::Texture&& other) noexcept
{
    assert(("you are moving empty texture, why?", !(source != nullptr)));
    source = other.source;
    size = other.size;
    file_path = std::move(other.file_path);
    other.source = nullptr;

    return *this;
}

palka::Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);
}

void palka::Texture::LoadFromFile(std::string_view path,Window& win)
{
    assert(!(source != nullptr));
    source = IMG_LoadTexture(win.getContext(), path.data());
    int w, h;
    SDL_QueryTexture(source, NULL, NULL, &w, &h);
    size = {w, h};
    file_path = path;
}

palka::Texture::Texture(std::string_view path, palka::Vec2i size, Window& win) : size(size), file_path(path),
                                                                                            source(nullptr)
{
    LoadFromFile(path,win);
}

unsigned int palka::Texture::getAlpha() const
{
    Uint8 blend;
    SDL_GetTextureAlphaMod(source, &blend);
    return blend;
}

SDL_BlendMode palka::Texture::getBlendMode() const
{
    SDL_BlendMode blend;
    SDL_GetTextureBlendMode(source, &blend);
    return blend;
}

void palka::Texture::setAlpha(unsigned int alpha)
{
    SDL_SetTextureAlphaMod(source, alpha);
}

void palka::Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(source, blending);
}


#ifdef REFLECTION_CORE
#include <rttr/registration>
RTTR_REGISTRATION
{
    registration::enumeration<SDL_BlendMode>("SDL_BlendMode")
            (
                    value("SDL_BLENDMODE_ADD",     SDL_BlendMode::SDL_BLENDMODE_ADD),
                    value("SDL_BLENDMODE_BLEND",   SDL_BlendMode::SDL_BLENDMODE_BLEND),
                    value("SDL_BLENDMODE_INVALID", SDL_BlendMode::SDL_BLENDMODE_INVALID),
                    value("SDL_BLENDMODE_MOD",     SDL_BlendMode::SDL_BLENDMODE_MOD),
                    value("SDL_BLENDMODE_MUL",     SDL_BlendMode::SDL_BLENDMODE_MUL),
                    value("SDL_BLENDMODE_NONE",    SDL_BlendMode::SDL_BLENDMODE_NONE)
            );
    using namespace rttr;
    registration::class_<palka::Texture>("Texture")
            .constructor<>()
            .property("blend mode", &palka::Texture::getBlendMode, &palka::Texture::setBlendMode)
            .property("alpha", &palka::Texture::getAlpha, &palka::Texture::setAlpha);
}
#endif
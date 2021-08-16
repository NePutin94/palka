//
// Created by NePutin on 6/23/2021.
//

#include "Texture.h"
#ifdef REFLECTION_CORE

#include <rttr/registration>

RTTR_REGISTRATION
{
    registration::enumeration<SDL_BlendMode>("SDL_BlendMode")
            (
                    value("SDL_BLENDMODE_ADD", SDL_BlendMode::SDL_BLENDMODE_ADD),
                    value("SDL_BLENDMODE_BLEND", SDL_BlendMode::SDL_BLENDMODE_BLEND),
                    value("SDL_BLENDMODE_INVALID", SDL_BlendMode::SDL_BLENDMODE_INVALID),
                    value("SDL_BLENDMODE_MOD", SDL_BlendMode::SDL_BLENDMODE_MOD),
                    value("SDL_BLENDMODE_MUL", SDL_BlendMode::SDL_BLENDMODE_MUL),
                    value("SDL_BLENDMODE_NONE", SDL_BlendMode::SDL_BLENDMODE_NONE)
            );
    using namespace rttr;
    registration::class_<palka::Texture>("Texture")
            .constructor<>()
            .property("blend mode", &palka::Texture::getBlendMode, &palka::Texture::setBlendMode)
            .property("alpha", &palka::Texture::getAlpha, &palka::Texture::setAlpha);
}

#endif
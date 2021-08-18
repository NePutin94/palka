//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_TEXTURE_H
#define PALKA_TEXTURE_H

#include <SDL.h>
#include <string_view>
#include <SDL_image.h>
#include <string>
#include <cassert>
#include "Rect.h"
#include "Window.h"

#ifdef REFLECTION_CORE
#include <rttr/type>
#include <rttr/registration_friend>
#endif

namespace palka
{
    class Texture
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
#endif
    private:
        SDL_Texture* source = nullptr;
        std::string file_path;
        Vec2i size;
        bool copy = false;
    public:
        Texture() = default;

        Texture(const Texture& other) = delete;

        Texture(Texture&& other) noexcept;

        Texture& operator=(Texture&& other) noexcept;

        explicit Texture(std::string_view path, Vec2i size, SDL_Renderer* renderer = Window::GetContext());

        void LoadFromFile(std::string_view path);

        void setBlendMode(SDL_BlendMode blending);

        SDL_BlendMode getBlendMode() const;

        void setAlpha(unsigned int alpha);

        unsigned int getAlpha() const;

        ~Texture()
        {
            SDL_DestroyTexture(source);
        }

        [[nodiscard]] Vec2i getSize() const
        {
            return size;
        }

        [[nodiscard]] std::string_view getFilePath() const
        {
            return file_path;
        }

        [[nodiscard]] SDL_Texture* getTextureP()
        {
            return source;
        }
    };
}

#endif //PALKA_TEXTURE_H

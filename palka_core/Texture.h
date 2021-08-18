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

        Texture(Texture&& other) noexcept
        {
            assert(("Can't move", !(source != nullptr)));
            source = other.source;
            size = other.size;
            file_path = std::move(other.file_path);

            other.source = nullptr;
        }

        Texture& operator=(Texture&& other) noexcept
        {
            assert(("Can't move", !(source != nullptr)));
            source = other.source;
            size = other.size;
            file_path = std::move(other.file_path);

            other.source = nullptr;
        }

        explicit Texture(std::string_view path, Vec2i size, SDL_Renderer* renderer = Window::GetContext()) : size(size), file_path(path),
                                                                                                             source(nullptr)
        {
            source = IMG_LoadTexture(Window::GetContext(), path.data());
        }

        void LoadFromFile(std::string_view path)
        {
            assert(!(source != nullptr));
            source = IMG_LoadTexture(Window::GetContext(), path.data());
            int w, h;
            SDL_QueryTexture(source, NULL, NULL, &w, &h);
            size = {w, h};
            file_path = path;
        }

        void setBlendMode(SDL_BlendMode blending)
        {
            SDL_SetTextureBlendMode(source, blending);
        }

        auto getBlendMode() const
        {
            SDL_BlendMode blend;
            SDL_GetTextureBlendMode(source, &blend);
            return blend;
        }

        void setAlpha(unsigned int alpha)
        {
            SDL_SetTextureAlphaMod(source, alpha);
        }

        unsigned int getAlpha() const
        {
            Uint8 blend;
            SDL_GetTextureAlphaMod(source, &blend);
            return blend;
        }

        ~Texture()
        {
            SDL_DestroyTexture(source);
        }

        [[nodiscard]] auto getSize() const
        {
            return size;
        }

        [[nodiscard]] auto getFilePath() const
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

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
#include "Context.h"

namespace palka
{
    class Texture
    {
    private:
        SDL_Texture* source = nullptr;
        std::string file_path;
        Vec2i size;
    public:
        Texture() = default;

        explicit Texture(std::string_view path, Vec2i size, SDL_Renderer* renderer = Context::GetContext()) : size(size), file_path(path),
                                                                                                              source(nullptr)
        {
            source = IMG_LoadTexture(Context::GetContext(), path.data());
        }

        void LoadFromFile(std::string_view path)
        {
            assert(!(source != nullptr));
            source = IMG_LoadTexture(Context::GetContext(), path.data());
            file_path = path;
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

        void draw(Vec2i pos, SDL_Renderer* renderer = Context::GetContext())
        {
            //SDL_Rect s{0, 0, size.x, size.y};
            SDL_Rect d{pos.x, pos.y, pos.x + size.x, pos.y + size.y};
            SDL_Rect rct2;
            rct2.x = rct2.y = 100;
            rct2.w = rct2.h = 200;
            SDL_RenderCopy(Context::GetContext(), source, 0, &rct2);
        }

        [[nodiscard]] SDL_Texture* getSdl() const
        {
            return source;
        }
    };
}

#endif //PALKA_TEXTURE_H

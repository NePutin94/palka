//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_TEXTURE_H
#define PALKA_TEXTURE_H

#include <string_view>
#include <string>
#include <cassert>
#include "Rect.h"
#include <GLFW/glfw3.h>

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
        std::string file_path;
        Vec2i size;
        GLuint textureID = 0;
        bool valid = true;

    public:
        Texture() = default;

        Texture(const Texture& other) = delete;

        Texture(Texture&& other) noexcept;

        Texture& operator=(Texture&& other) noexcept;

        explicit Texture(std::string_view path, Vec2i size);

        void LoadFromFile(std::string_view path);

        ~Texture()
        {
            if (valid)
                glDeleteTextures(1, &textureID);
        }
        void bind()
        {
            glBindTexture(GL_TEXTURE_2D, textureID);
        }

        Vec2i getSize() const
        {
            return size;
        }

        std::string_view getFilePath() const
        {
            return file_path;
        }

    };
}

#endif //PALKA_TEXTURE_H

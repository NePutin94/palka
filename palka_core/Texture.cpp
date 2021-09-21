//
// Created by NePutin on 6/23/2021.
//

#include "Texture.h"


#define STB_IMAGE_IMPLEMENTATION

#include "../stb_image.h"


palka::Texture& palka::Texture::operator=(palka::Texture&& other) noexcept
{
    textureID = other.textureID;
    valid = other.valid;
    size = other.size;
    file_path = std::move(other.file_path);
    other.valid = false;
    other.textureID = 0;
    other.size = {};
    return *this;
}

palka::Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);
}

void palka::Texture::LoadFromFile(std::string_view path)
{
    assert(!valid);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int x, y, n;
    unsigned char* data = stbi_load(path.data(), &x, &y, &n, 0);
    size.x = x;
    size.y = y;
    if (n == 3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (n == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

palka::Texture::Texture(std::string_view path, palka::Vec2i size) : size(size), file_path(path)
{
    LoadFromFile(path);
}

#ifdef REFLECTION_CORE

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<palka::Texture>("Texture")
            .constructor<>();
}

#endif
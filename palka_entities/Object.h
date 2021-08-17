//
// Created by NePutin on 8/5/2021.
//

#ifndef PALKA_OBJECT_H
#define PALKA_OBJECT_H

#include "../palka_core/Sprite.h"

namespace palka
{
    class Object : public TransformObject
    {
    public:
        std::string name;
        bool isActive;
        Texture texture;
        Sprite sprite;

    public:
        explicit Object(std::string_view name) : name(name), isActive(true)
        {}

        explicit Object(Texture textrue, std::string_view name) : name(name), isActive(true), texture(std::move(textrue))
        {

        }

        bool IsActive() const
        {
            return isActive;
        }

        std::string getName() const
        {
            return name;
        }

        void setTexture(Texture&& txt, RectI rect)
        {
            texture = std::move(txt);
            sprite.setTexture(texture, rect);
        }

        operator Drawable&()
        {
            sprite.copy((TransformObject) *this);
            return sprite;
        }
    };
}
#endif //PALKA_OBJECT_H

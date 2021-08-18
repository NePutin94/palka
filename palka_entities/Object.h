//
// Created by NePutin on 8/5/2021.
//

#ifndef PALKA_OBJECT_H
#define PALKA_OBJECT_H

#include "../palka_core/Sprite.h"

#ifdef REFLECTION_CORE
#include <rttr/type>
#include <rttr/wrapper_mapper.h>
#include <rttr/registration_friend>
#endif

namespace palka
{
    class Object : public TransformObject
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
        //Raw_Ptr<Texture> debug_texture;
#endif
    public:
        std::string name;
        bool isActive;
        Texture texture;
        Sprite sprite;
        void updateTexture(Texture&& txt)
        {
            texture = std::move(txt);
           // debug_texture.set_data(&texture);
        }
    public:
        explicit Object(std::string_view name) : name(name), isActive(true)
        {}

        explicit Object(Texture&& textrue, std::string_view name) : name(name), isActive(true)
        {
            setTexture(std::move(texture), {});
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
            updateTexture(std::move(txt));
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

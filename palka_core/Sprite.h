//
// Created by NePutin on 6/26/2021.
//

#ifndef PALKA_SPRITE_H
#define PALKA_SPRITE_H

#include <utility>
#include "Drawable.h"
#include "Texture.h"
#include "Rect.h"
#include "Matrix.h"
#include "Transform.h"
#include "TransformObject.h"

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/wrapper_mapper.h>
#include <rttr/registration_friend>

#endif
template<typename T>
class Raw_Ptr
{
public:
    Raw_Ptr() : m_data(nullptr) {}
    explicit Raw_Ptr(T* obj) : m_data(obj) {}
    explicit Raw_Ptr(T) : m_data(nullptr) {}
    T* get_data() const { return m_data; }
    void set_data(T* obj) { m_data = obj; }
private:
    T* m_data;
};
namespace rttr
{
    template<typename T>
    struct wrapper_mapper<Raw_Ptr<T>>
    {
        using wrapped_type  = decltype(std::declval<Raw_Ptr<T>>().get_data());
        using type          = Raw_Ptr<T>;
        inline static wrapped_type get(const type& obj)
        {
            return obj.get_data();
        }
        inline static type create(const wrapped_type& value)
        {
            return Raw_Ptr<T>(std::move(value));
        }
        template<typename U>
        inline static Raw_Ptr<U> convert(const type& source, bool& ok)
        {
            if (auto obj = rttr_cast<typename Raw_Ptr<U>::wrapped_type*>(&source.get_data()))
            {
                ok = true;
                return Raw_Ptr<U>(*obj);
            }
            else
            {
                ok = false;
                return Raw_Ptr<U>();
            }
        }
    };
}
namespace palka
{
    class Sprite : public Drawable, public TransformObject
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE(TransformObject)
        RTTR_REGISTRATION_FRIEND
#endif
    private:
        Raw_Ptr<Texture> txt;
        RectI src;
        SDL_RendererFlip flip_p = SDL_FLIP_NONE;
    public:

        Sprite() = default;

        Sprite(Texture& tex);

        void setTexture(Texture& tex, RectI rect = {});

        void setTextureRect(RectI rect);

        void setFlip(SDL_RendererFlip flip_p)
        { this->flip_p = flip_p; }

        SDL_RendererFlip getFlip()
        { return flip_p; }

        RectI getTextureRect() const;

        RectI getLocalRect() const;

        RectF getGlobalRect() const;

        void draw(SDL_Renderer*, SDL_FPoint viewPos) const override;

        friend class Window;
    };
}
#endif //PALKA_SPRITE_H

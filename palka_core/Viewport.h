//
// Created by NePutin on 7/5/2021.
//

#ifndef PALKA_VIEWPORT_H
#define PALKA_VIEWPORT_H

#include "config.h"
#include "Vec2.h"
#include "Rect.h"
#include "Transform.h"

#include <rttr/type>
#include <rttr/registration_friend>
#include <utility>

using namespace rttr;
namespace palka
{
    class Viewport
    {
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
    private:
        Vec2f center;
        Vec2f scale = {1, 1};
    public:
        Viewport(const RectF& r) : center()
        {

        }

        [[nodiscard]] Vec2f getScale() const
        {
            return scale;
        }

        void setCenter(const Vec2f& c)
        {
            center = c;
        }

        [[nodiscard]] const auto& getCenter() const
        {
            return center;
        }

        void setScale(Vec2f sc)
        {
            scale = sc;
            //setSize({size.x * f, size.y * f});
        }

        template<class T>
        auto applyTranslate(Quad<T> q)
        {
            q.leftTop += getCenter();
            q.rightTop += getCenter();
            q.rightBottom += getCenter();
            q.leftBottom += getCenter();
            return q;
        }

        template<class T>
        auto applyTranslate(Vec2<T> q)
        {
            q += getCenter();
            return q;
        }
    };
}

#endif //PALKA_VIEWPORT_H

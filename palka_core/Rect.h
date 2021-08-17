//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_RECT_H
#define PALKA_RECT_H

#include <SDL_rect.h>
#include "Vec2.h"
#include "Matrix.h"
#include <utility>

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/registration_friend>

#endif

namespace palka
{
    template<class T>
    class Rect;

    template<class T>
    struct Quad
    {
        Quad() = default;

        Vec2<T> leftTop, rightTop, leftBottom, rightBottom;

        explicit Quad(std::array<Vec2<T>, 4> arr);

        explicit Quad(Rect<T> r);
        Quad<int> toInt()
        {
            Quad<int> q;
            q.leftTop = Vec2i(leftTop.x,leftTop.y);
            q.rightTop = Vec2i(rightTop.x,rightTop.y);
            q.leftBottom = Vec2i(leftBottom.x,leftBottom.y);
            q.rightBottom = Vec2i(rightBottom.x,rightBottom.y);
            return q;
        }
    };

    template<class T>
    class Rect
    {
#ifdef REFLECTION_CORE
    RTTR_ENABLE()

        RTTR_REGISTRATION_FRIEND
#endif
    public:
        T left, top, w, h;

        Rect() = default;

        Rect(T x, T y, T w, T h) : left(x), top(y), w(w), h(h)
        {}

        Rect(const Rect&) = default;

        template<class T2>
        bool contains(Vec2<T2>);

        bool intersects(Rect, Rect&);

        SDL_Rect getRect() const
        {
            return {(int) left, (int) top, (int) w, (int) h};
        }

        SDL_FRect getRectF() const
        {
            return {(float)left, (float)top, (float)w, (float)h};
        }

        std::array<Vec2<T>, 4> getPoints() const
        {

            return {Vec2<T>{this->left, this->top},
                    Vec2<T>{this->left + this->w, this->top},
                    Vec2<T>{this->left, this->top + this->h},
                    Vec2<T>{this->left + this->w, this->top + this->h}};
        }

        Quad<T> rotate(float angle, Vec2i origin)
        {
            palka::Matrix2DRotate<float> mat2(angle);
            auto points = getPoints();
            Vec2<T> top1 = points[0];
            Vec2<T> top2 = points[1];
            Vec2<T> bottom1 = points[2];
            Vec2<T> bottom2 = points[3];
            top1 = top1 - origin;
            top2 = top2 - origin;
            bottom1 = bottom1 - origin;
            bottom2 = bottom2 - origin;
            top1 = mat2 * top1;
            top2 = mat2 * top2;
            bottom1 = mat2 * bottom1;
            bottom2 = mat2 * bottom2;
            top1 += origin;
            top2 += origin;
            bottom1 += origin;
            bottom2 += origin;
            return Quad<T>({top1, top2, bottom1, bottom2});
        }
    };

    template<class T>
    Quad<T>::Quad(Rect<T> r)
    {
        auto arr = r.getPoints();
        leftTop = arr[0];
        rightTop = arr[1];
        leftBottom = arr[2];
        rightBottom = arr[3];
    }

    template<class T>
    Quad<T>::Quad(std::array<Vec2<T>, 4> arr)
    {
        leftTop = arr[0];
        rightTop = arr[1];
        leftBottom = arr[2];
        rightBottom = arr[3];
    }

    template<class T>
    template<class T2>
    bool Rect<T>::contains(Vec2<T2> vec)
    {
        T minX = std::min(left, static_cast<T>(left + w));
        T maxX = std::max(left, static_cast<T>(left + w));
        T minY = std::min(top, static_cast<T>(top + h));
        T maxY = std::max(top, static_cast<T>(top + h));
        return (vec.x >= minX) && (vec.x < maxX) && (vec.y >= minY) && (vec.y < maxY);
    }

    template<class T>
    bool Rect<T>::intersects(Rect<T> r2, Rect<T>& intersection)
    {
        T r1MinX = std::min(left, static_cast<T>(left + w));
        T r1MaxX = std::max(left, static_cast<T>(left + w));
        T r1MinY = std::min(top, static_cast<T>(top + h));
        T r1MaxY = std::max(top, static_cast<T>(top + h));

        T r2MinX = std::min(r2.left, static_cast<T>(r2.left + r2.w));
        T r2MaxX = std::max(r2.left, static_cast<T>(r2.left + r2.w));
        T r2MinY = std::min(r2.top, static_cast<T>(r2.top + r2.h));
        T r2MaxY = std::max(r2.top, static_cast<T>(r2.top + r2.h));

        T interLeft = std::max(r1MinX, r2MinX);
        T interTop = std::max(r1MinY, r2MinY);
        T interRight = std::min(r1MaxX, r2MaxX);
        T interBottom = std::min(r1MaxY, r2MaxY);

        if ((interLeft < interRight) && (interTop < interBottom))
        {
            intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
            return true;
        } else
        {
            intersection = Rect<T>(0, 0, 0, 0);
            return false;
        }
    }

    using RectF = Rect<float>;
    using RectI = Rect<int>;
}

#endif //PALKA_RECT_H
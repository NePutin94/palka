//
// Created by NePutin on 6/23/2021.
//

#ifndef PALKA_VEC2_H
#define PALKA_VEC2_H

#include "config.h"
#include <cmath>
#include <string>

#ifdef REFLECTION_CORE

#include <rttr/type>
#include <rttr/registration_friend>

#endif
namespace palka
{
    template<class T>
    class Vec2
    {
#ifdef REFLECTION_CORE
    RTTR_ENABLE()

        RTTR_REGISTRATION_FRIEND
#endif
    public:
        T x = 0;
        T y = 0;

        Vec2() = default;

        Vec2(const Vec2&) = default;

        Vec2(T x, T y) noexcept : x(x), y(y)
        {}

        static constexpr Vec2 Zero()
        { return Vec2((T)0, (T)0); }

        Vec2 operator+(Vec2 val);

        Vec2 operator+=(Vec2 val);

        Vec2 operator-(Vec2 val);

        Vec2 operator-=(Vec2 val);

        Vec2 operator/(Vec2 val);

        Vec2 operator/=(Vec2 val);

        Vec2 operator*(Vec2 val);

        Vec2 operator*=(Vec2 val);

        Vec2 operator+(T val);

        Vec2 operator-(T val);

        Vec2 operator/(T val);

        Vec2 operator*(T val);

        bool operator==(Vec2 val);

        bool operator!=(Vec2 val);

        Vec2 abs();

        T lenght();

        T dot();

        Vec2 normalize();

        std::string toString()
        {
            return "x: " + std::to_string(x) + " y: " + std::to_string(y);
        }
    };

    template<class T>
    Vec2<T> rotateBy(const Vec2<T>& vec, float degrees, const Vec2<T>& center)
    {
        degrees *= M_PI / 180.f;
        const float cs = cos(degrees);
        const float sn = sin(degrees);
        auto _vec = vec;
        _vec.x -= center.x;
        _vec.y -= center.y;

        T nx = (T) (_vec.x * cs - _vec.y * sn);
        T ny = (T) (_vec.x * sn + _vec.y * cs);

        _vec.x = nx;
        _vec.y = ny;

        _vec.x += center.x;
        _vec.y += center.y;
        return _vec;
    }

    using Vec2f = Vec2<float>;
    using Vec2i = Vec2<int>;

    template<class T>
    Vec2<T> Vec2<T>::operator+(Vec2 val)
    {
        return Vec2(this->x + val.x, this->y + val.y);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator-(Vec2 val)
    {
        return Vec2(this->x - val.x, this->y - val.y);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator+(T val)
    {
        return Vec2(this->x + val, this->y + val);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator-(T val)
    {
        return Vec2(this->x - val, this->y - val);
    }

    template<class T>
    T Vec2<T>::lenght()
    {
        return sqrt(this->dot());
    }

    template<class T>
    T Vec2<T>::dot()
    {
        return this->x * this->x + this->y * this->y;
    }

    template<class T>
    Vec2<T> Vec2<T>::abs()
    {
        return Vec2(std::abs(this->x), std::abs(this->y));
    }

    template<class T>
    Vec2<T> Vec2<T>::normalize()
    {
        auto l = this->lenght();
        return (*this) / l;
    }

    template<class T>
    Vec2<T> Vec2<T>::operator*(T val)
    {
        return Vec2(this->x * val, this->y * val);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator/(T val)
    {
        return Vec2(this->x / val, this->y / val);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator-=(Vec2 val)
    {
        *this = *this - val;
        return (*this);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator+=(Vec2 val)
    {
        *this = *this + val;
        return *this;
    }

    template<class T>
    Vec2<T> Vec2<T>::operator*(Vec2 val)
    {
        return Vec2(val.x * this->x, val.y * this->y);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator/(Vec2 val)
    {
        return {x / val.x, y / val.y};
    }

    template<class T>
    bool Vec2<T>::operator==(Vec2 val)
    {
        return val.x == this->x && val.y == this->y;
    }

    template<class T>
    bool Vec2<T>::operator!=(Vec2 val)
    {
        return !(*this == val);
    }

    template<class T>
    Vec2<T> Vec2<T>::operator/=(Vec2 val)
    {
        *this = *this / val;
        return *this;
    }

    template<class T>
    Vec2<T> Vec2<T>::operator*=(Vec2 val)
    {
        *this = *this * val;
        return *this;
    }
}
#endif //PALKA_VEC2_H

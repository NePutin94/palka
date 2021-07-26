//
// Created by NePutin on 7/7/2021.
//

#ifndef PALKA_TRANSFORM_H
#define PALKA_TRANSFORM_H

#include "Vec2.h"

#ifdef REFLECTION_CORE
#include <rttr/type>
#include <rttr/registration_friend>
#endif

namespace palka
{
    class Transform
    {
#ifdef REFLECTION_CORE
        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND
#endif
    private:
        float matrix[16];
    public:
        Transform()
        {
            matrix[0] = 1.f; matrix[4] = 0.f; matrix[8]  = 0.f; matrix[12] = 0.f;
            matrix[1] = 0.f; matrix[5] = 1.f; matrix[9]  = 0.f; matrix[13] = 0.f;
            matrix[2] = 0.f; matrix[6] = 0.f; matrix[10] = 1.f; matrix[14] = 0.f;
            matrix[3] = 0.f; matrix[7] = 0.f; matrix[11] = 0.f; matrix[15] = 1.f;
        }

        Transform(float a00, float a01, float a02,
                  float a10, float a11, float a12,
                  float a20, float a21, float a22)
        {
            matrix[0] = a00; matrix[4] = a01; matrix[8]  = 0.f; matrix[12] = a02;
            matrix[1] = a10; matrix[5] = a11; matrix[9]  = 0.f; matrix[13] = a12;
            matrix[2] = 0.f; matrix[6] = 0.f; matrix[10] = 1.f; matrix[14] = 0.f;
            matrix[3] = a20; matrix[7] = a21; matrix[11] = 0.f; matrix[15] = a22;
        }

        void combine(const Transform& tf)
        {
            const float* a = matrix;
            const float* b = tf.matrix;
            auto _00 = a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3];
            auto _01 = a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7];
            auto _02 = a[0] * b[12] + a[4] * b[13] + a[12] * b[15];
            auto _10 = a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3];
            auto _11 = a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7];
            auto _12 = a[1] * b[12] + a[5] * b[13] + a[13] * b[15];
            auto _20 = a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3];
            auto _21 = a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7];
            auto _22 = a[3] * b[12] + a[7] * b[13] + a[15] * b[15];
            *this = Transform(_00, _01, _02,
                              _10, _11, _12,
                              _20, _21, _22);
        }

        auto translate(float x, float y)
        {
            Transform translate(1,0, x,
                                0,1, y,
                                0,0,1);
            return combine(translate);
        }

        auto scale(float x, float y)
        {
            Transform scale(    x,0, 0,
                            0,    y, 0,
                            0,0,1);
            return combine(scale);
        }

        auto scale(float x, float y, Vec2f center)
        {
            Transform scale(    x,0, center.x * (1 - center.x),
                            0,    y, center.y * (1 - center.y),
                            0,0,1);
            return combine(scale);
        }

        auto rotate(float angle)
        {
            float rad = angle * M_PI / 180.f;
            float cos = std::cos(rad);
            float sin = std::sin(rad);
            Transform rot(  cos, -sin, 0,
                            cos,  sin, 0,
                          0,0,1);
            return combine(rot);
        }

        auto rotate(float angle, Vec2f center)
        {
            float rad = angle * M_PI / 180.f;
            float cos = std::cos(rad);
            float sin = std::sin(rad);
            Transform rot(  cos, -sin,center.x * (1 - cos) + center.y * sin,
                            cos,  sin,center.y * (1 - cos) - center.x * sin,
                          0,0,1);
            return combine(rot);
        }

        auto& getMatrix()
        {
            return matrix;
        }

        [[nodiscard]] Transform getInverse() const
        {
            float det = matrix[0] * (matrix[15] * matrix[5] - matrix[7] * matrix[13]) -
                    matrix[1] * (matrix[15] * matrix[4] - matrix[7] * matrix[12]) +
                    matrix[3] * (matrix[13] * matrix[4] - matrix[5] * matrix[12]);
            if (det != 0.f)
            {
                return Transform(  (matrix[15] * matrix[5] - matrix[7] * matrix[13]) / det,
                                  -(matrix[15] * matrix[4] - matrix[7] * matrix[12]) / det,
                                   (matrix[13] * matrix[4] - matrix[5] * matrix[12]) / det,
                                  -(matrix[15] * matrix[1] - matrix[3] * matrix[13]) / det,
                                   (matrix[15] * matrix[0] - matrix[3] * matrix[12]) / det,
                                  -(matrix[13] * matrix[0] - matrix[1] * matrix[12]) / det,
                                   (matrix[7]  * matrix[1] - matrix[3] * matrix[5])  / det,
                                  -(matrix[7]  * matrix[0] - matrix[3] * matrix[4])  / det,
                                   (matrix[5]  * matrix[0] - matrix[1] * matrix[4])  / det);
            }
            else
            {
                return Transform();
            }
        }

        Vec2f transformPoint(Vec2f p) const
        {
            return Vec2f(matrix[0] * p.x + matrix[4] * p.y + matrix[12],
                         matrix[1] * p.x + matrix[5] * p.y + matrix[13]);
        }
    };
}

#endif //PALKA_TRANSFORM_H

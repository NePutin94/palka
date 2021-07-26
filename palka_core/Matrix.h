
//
// Created by NePutin on 6/26/2021.
//

#ifndef PALKA_MATRIX_H
#define PALKA_MATRIX_H

#include <array>
#include "Vec2.h"
#include <cstring>

namespace palka
{
    template<class T>
    class Matrix2D
    {
    protected:
        T mat[2][2];
    public:

        Vec2 <T> operator*(Vec2 <T> vec)
        {
            T res[2] = {0, 0};
            T _vec[2] = {vec.x, vec.y};
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    res[i] += mat[i][j] * _vec[j];
            return Vec2<T>(res[0], res[1]);
        }

        T* getMatrix()
        {
            return mat;
        }
    };

    template<class T>
    class Matrix2DRotate : public Matrix2D<T>
    {
    private:
        // T mat[2][2];
    public:
        explicit Matrix2DRotate(T angle)
        {
            double radians = (angle * M_PI) / 180;
            T x[2][2] = {{(T) cos(radians), -(T) sin(radians)},
                         {(T) sin(radians), (T) cos(radians)}};
            memcpy(this->mat, x, 2 * 2 * sizeof(T));
        }

        T& operator()(int r, int c)
        { return this->mat[r][c]; }
    };

    template<class T>
    class MatrixScale2D : public Matrix2D<T>
    {
    private:
        // T mat[2][2];
    public:
        explicit MatrixScale2D(T scale)
        {
            T x[2][2] = {{scale, 0},
                         {0,     scale}};
            memcpy(this->mat, x, 2 * 2 * sizeof(T));
        }

        T& operator()(int r, int c)
        { return this->mat[r][c]; }
    };

    template<class T1, class T2>
    Vec2 <T1> operator*(Matrix2DRotate<T2> mat, Vec2 <T1> vec)
    {
        auto res = mat.operator*(Vec2<T2>{(T2) vec.x, (T2) vec.y});
        return Vec2<T1>{res.x, res.y};
    }

    template<class T2>
    Vec2 <T2> operator*(MatrixScale2D<T2> mat, Vec2 <T2> vec)
    {
        return mat.operator*(vec);
    }

    template<class T2>
    Vec2 <T2> operator*(Vec2 <T2> vec, MatrixScale2D<T2> mat)
    {
        return mat * vec;
    }
}

#endif //PALKA_MATRIX_H

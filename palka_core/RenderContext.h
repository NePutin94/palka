//
// Created by NePutin on 9/7/2021.
//

#ifndef PALKA_RENDERCONTEXT_H
#define PALKA_RENDERCONTEXT_H

#include "BlendMode.h"
#include "Texture.h"
#include "Transform.h"
#include "ShaderProgram.h"

namespace palka
{
    class RenderContext
    {
    public:
        ShaderProgram* shader;
        UniformBuffer* buffer;
        BlendMode blend;
        Mat4f model_mat;

    public:
        RenderContext() : model_mat(Mat4f{1.f}), buffer(nullptr), shader(nullptr)
        {}

        RenderContext(ShaderProgram* shader, UniformBuffer* buffer = nullptr, Mat4f model_mat = Mat4f{1.f})
                : model_mat(model_mat), buffer(buffer), shader(shader)
        {}

        friend class Window;
    };
}

#endif //PALKA_RENDERCONTEXT_H

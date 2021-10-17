//
// Created by NePutin on 9/15/2021.
//

#ifndef PALKA_RENDERER_H
#define PALKA_RENDERER_H


#include "RenderContext.h"
#include "VertexData.h"
#include "Shader.h"
#include "Drawable.h"
#include "Viewport.h"
#include "VertexBuffer.h"
#include "TransformObject.h"
#include "Camera.h"
#include "VertexArrayObject.h"

namespace palka
{
    class Renderer
    {
    private:
        Viewport view;
        Vec2i size;
        Camera camera;
        Texture t;
    public:

        Renderer(Vec2i sz) : size(sz), view({0, 0, (float) sz.x, (float) sz.y}), camera(sz)
        {

        }

        void init()
        {
            t.LoadFromFile("Data\\tex\\debug.png");
        }

        void setSize(Vec2i sz)
        {
            size = sz;
            view.setSize(Vec2f(size.x, size.y));
        }

        Viewport& getViewport()
        {
            return view;
        }

        Camera& getCamera()
        {
            return camera;
        }

        void setup()
        {
            glReset();
        }

        void glReset()
        {
            glMatrixMode(GL_PROJECTION);
            glBindTexture(GL_TEXTURE_2D, 0);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        void clear(Color color = {0, 120, 120})
        {
            glClearColor(0, 120, 120, 255);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, size.x, size.y);
        }

        void applyBlend(BlendMode mode)
        {
            glEnable(GL_BLEND);
            glBlendFuncSeparate(
                    BlendMode::enumToGlConstant(mode.colorSrcFactor), BlendMode::enumToGlConstant(mode.colorDstFactor),
                    BlendMode::enumToGlConstant(mode.alphaSrcFactor), BlendMode::enumToGlConstant(mode.alphaDstFactor));
            glBlendEquationSeparate(
                    BlendMode::enumToGlConstant(mode.colorEquation),
                    BlendMode::enumToGlConstant(mode.alphaEquation));
        }

        void applyView()
        {
            glViewport(0, 0, size.x, size.y);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(view.getView().getMatrix());
            glMatrixMode(GL_MODELVIEW);
        }

        void draw(VertArray array, RenderContext context = {});

        glm::vec3 cubePositions[10] = {
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(2.0f, 5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3(2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f, 3.0f, -7.5f),
                glm::vec3(1.3f, -2.0f, -2.5f),
                glm::vec3(1.5f, 2.0f, -2.5f),
                glm::vec3(1.5f, 0.2f, -1.5f),
                glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        void VAODraw(VertexBuffer array, Shader s, RenderContext context = {});

        void VAODraw(VertexArrayObject array, Shader s, RenderContext context = {});

        void draw(const Drawable& d)
        {
            d.draw(*this);
        }
    };
}

#endif //PALKA_RENDERER_H

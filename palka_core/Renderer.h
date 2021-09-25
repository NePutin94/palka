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

namespace palka
{
    class Renderer
    {
    private:
        Viewport view;
        Vec2i size;
        Shader vertexShader;
        static std::map<unsigned int, GLuint> chache;

        void genBufffers(const Drawable& d)
        {
            //glGenVertexArrays(1, &d.DrawData.VAO);
            //glGenBuffers(1, &d.DrawData.VBO);
        }

    public:
        Renderer(Vec2i sz) : size(sz), view({0, 0, (float) sz.x, (float) sz.y}), vertexShader(Shader::FRAGMENT)
        {

        }

        void init()
        {

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
//            glEnableClientState(GL_VERTEX_ARRAY);
//            glEnableClientState(GL_COLOR_ARRAY);
//            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        void clear(Color color = {0, 120, 120})
        {
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT);
            applyView();
        }

        void applyBlend(BlendMode mode)
        {
            glBlendFuncSeparate(
                    BlendMode::enumToGlConstant(mode.colorSrcFactor), BlendMode::enumToGlConstant(mode.colorDstFactor),
                    BlendMode::enumToGlConstant(mode.alphaSrcFactor), BlendMode::enumToGlConstant(mode.alphaDstFactor));
            glBlendEquationSeparate(
                    BlendMode::enumToGlConstant(mode.colorEquation),
                    BlendMode::enumToGlConstant(mode.alphaEquation));
        }

        void applyView_m()
        {
            glViewport(0, 0, size.x, size.y);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(view.getView().getMatrix());
            glMatrixMode(GL_MODELVIEW);
        }

        void applyView()
        {
            glViewport(0, 0, size.x, size.y);
        }

        void draw(VertArray array, RenderContext context = {})
        {
            glReset();
            glLoadMatrixf(context.transform.getMatrix());
            applyBlend(context.blend);
            applyView_m();
            if (context.texture != nullptr)
                context.texture->bind();

            Vertex* pointer = &array[0];
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glVertexPointer(2,
                            GL_FLOAT,
                            sizeof(Vertex),
                            &pointer->pos.x);

            glColorPointer(3,
                           GL_UNSIGNED_BYTE,
                           sizeof(Vertex),
                           &pointer->color.r);

            glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &pointer->texCoord.x);

            glDrawArrays(VertArray::type_to_gl(array.getType()), static_cast<GLint>(0), array.getSize());

            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        void VAODraw(VertexBuffer array, Shader s, RenderContext context = {})
        {
            glReset();
            applyBlend(context.blend);
            applyView();
            TransformObject t;
            t.setPosition({120, 120});

            s.updateUBO(context.transform.getMatrix(), 0, sizeof(float[16]));
            s.updateUBO(view.getView().getMatrix(), sizeof(float[16]), sizeof(float[16]));

            //s.setValue("modelMat", context.transform);
            //s.setValue("projMat", view.getView());
            s.setValue("viewMat", t.getTransform());
            if (context.texture != nullptr)
                context.texture->bind();

            glUseProgram(s.getId());
//            glBindVertexArray(VAO);
            array.bind();
            glDrawArrays(GL_QUADS, static_cast<GLint>(0), array.getSize());
            // glUseProgram(0);
        };

        void draw(const Drawable& d)
        {
            d.draw(*this);
        }
    };
}

#endif //PALKA_RENDERER_H

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
            vertexShader.loadVF("Data\\Shaders\\Default.frag","Data\\Shaders\\Default.vert");
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

        void applyView()
        {
            glViewport(0, 0, size.x, size.y);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(view.getView().getMatrix());
            glMatrixMode(GL_MODELVIEW);
        }

        void draw(VertArray array, RenderContext context = {})
        {
            glReset();
            glLoadMatrixf(context.transform.getMatrix());
            applyBlend(context.blend);
            applyView();
            if (context.texture != nullptr)
                context.texture->bind();

            Vertex* pointer = &array[0];

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

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }

        struct _Vertex
        {
            Vec2f position;
            unsigned char color[3] = {255,0,0};
        };

        void initVbo(VertArray array)
        {
            Vertex* pointer = &array[0];

//            Vertex vert[4] = {{{0,   0},   Color{255, 0, 0}},
//                              {{100, 0},   Color{255, 0, 0}},
//                              {{100, 100}, Color{255, 0, 0}},
//                              {{0,   100}, Color{255, 0, 0}}};
//            std::vector<_Vertex> vert = {{{0,   0}},
//                                         {{100, 0}},
//                                         {{100, 100}},
//                                         {{0,   100}}};
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO1);
            glBindVertexArray(VAO);

            GLint vertexAttribCoords = glGetAttribLocation(vertexShader.getId(), "aCoords");
            GLint vertexAttribColor = glGetAttribLocation(vertexShader.getId(), "aColor");

            glBindBuffer(GL_ARRAY_BUFFER, VBO1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &pointer->pos.x, GL_STATIC_DRAW);

            glVertexAttribPointer(vertexAttribCoords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(vertexAttribCoords);

            glVertexAttribPointer(vertexAttribColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(16));
            glEnableVertexAttribArray(vertexAttribColor);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vec2f) * 4, &vert->position.x);
            //glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vec2f) * 4, sizeof(_Vertex) * 4, &vert->color[0]);
            //GLuint attributeLocation = glGetAttribLocation(vertexShader.getId(), "aCoords");
            //GLuint asd = glGetAttribLocation(vertexShader.getId(), "aColor");
            //glEnableVertexAttribArray(attributeLocation);
            //glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), );
//            glGenBuffers(1, &VBO2);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(_Vertex) * 4, &vert.data()->c.r, GL_STATIC_DRAW);

//            glGenBuffers(1, &VBO3);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO3);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &pointer->texCoord.x, GL_STATIC_DRAW);
//            glTexCoordPointer(2, GL_FLOAT, 0, 0);
        }

        GLuint VBO1, VAO;

        void VBODraw(VertArray array, RenderContext context = {})
        {
            glReset();
            glLoadMatrixf(context.transform.getMatrix());
            applyBlend(context.blend);
            applyView();
            if (context.texture != nullptr)
                context.texture->bind();

//            Vertex* pointer = &array[0];
//            auto test = offsetof(Vertex, color);
//            Vertex v;
//            auto test2 = (char*) &v.color - (char*) &v.pos;
//            _Vertex v2;
//            auto test5 = (char*) &v2.color - (char*) &v2.position;
//            auto test3 = sizeof(Vec2f);
           // glBindBuffer(GL_ARRAY_BUFFER, VBO1);
           // glVertexPointer(2, GL_FLOAT, sizeof(Vertex), 0);
           // glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*) (16));
           // glBindBuffer(GL_ARRAY_BUFFER, 0);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//            glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);
//            glBindBuffer(GL_ARRAY_BUFFER, 0);
//            glBindBuffer(GL_ARRAY_BUFFER, VBO3);
//            glTexCoordPointer(2, GL_FLOAT, 0, 0);


           // glBindBuffer(GL_ARRAY_BUFFER, VBO1);

            // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
            glUseProgram(vertexShader.getId());
            glBindVertexArray(VAO);

            //glEnableClientState(GL_VERTEX_ARRAY);
            //glEnableClientState(GL_COLOR_ARRAY);
            glDrawArrays(VertArray::type_to_gl(array.getType()), static_cast<GLint>(0), 4);
           // glDisableClientState(GL_COLOR_ARRAY);
            //glDisableClientState(GL_VERTEX_ARRAY);
            //glBindBuffer(GL_ARRAY_BUFFER, 0);
            glUseProgram(0);
        };

        void draw(const Drawable& d)
        {
            d.draw(*this);
        }
    };
}

#endif //PALKA_RENDERER_H

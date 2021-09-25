//
// Created by NePutin on 9/25/2021.
//

#ifndef PALKA_VERTEXBUFFER_H
#define PALKA_VERTEXBUFFER_H

#include <glad/gl.h>
#include "VertexData.h"

namespace palka
{
    class VertexBuffer
    {
    public:
        void create(int size)
        {
            _size = size;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, 0, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void update(Vertex* v, int size, unsigned int shaderProgram)
        {
            GLint vaCoords = glGetAttribLocation(shaderProgram, "aCoords");
            GLint vaColor = glGetAttribLocation(shaderProgram, "aColor");
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            if (size > _size)
            {
                _size = size;
                glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size, 0, GL_STATIC_DRAW);
            }
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * size, &v->pos.x);

            glVertexAttribPointer(vaCoords, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(vaCoords);

            glVertexAttribPointer(vaColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*) (16));
            glEnableVertexAttribArray(vaColor);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void bind()
        {
            glBindVertexArray(VAO);
        }

        void unbind()
        {
            glBindVertexArray(0);
        }

        int getSize()
        {
            return _size;
        }

    private:
        unsigned int VBO, VAO;
        int _size;
    };
}

#endif //PALKA_VERTEXBUFFER_H

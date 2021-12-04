//
// Created by NePutin on 9/28/2021.
//

#ifndef PALKA_VERTEXARRAYOBJECT_H
#define PALKA_VERTEXARRAYOBJECT_H

#include "VertexBufferObject.h"

namespace palka
{
    class VertexArrayObject
    {
    public:
        VertexArrayObject() = default;
        VertexArrayObject(VertexArrayObject&&) = default;

        void create(int size)
        {
            this->size = size;
            glGenVertexArrays(1, &VAO);
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
            return size;
        }

        virtual void setPointers(VertexBufferObject& vbo, size_t type_size)
        {
            bind();
            vbo.bind();
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, type_size, 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, type_size, (void*) (24));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, type_size, (void*) (32));
            glEnableVertexAttribArray(2);

            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, type_size, (void*) (40));
            glEnableVertexAttribArray(3);

            vbo.unbind();
            unbind();
        }

        void setPointer_u(VertexBufferObject& vbo, int bind_point, size_t size_type, int type, size_t stride, size_t offset)
        {
            vbo.bind();
            glVertexAttribPointer(bind_point, size_type, type, GL_FALSE, stride, (void*) offset);
            glEnableVertexAttribArray(bind_point);
            vbo.unbind();
        }

    private:
        unsigned int VAO;
        int size;
    };
}

#endif //PALKA_VERTEXARRAYOBJECT_H

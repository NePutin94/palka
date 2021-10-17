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

        template<class T>
        void setPointers()
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(T), 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(T), (void*) (24));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(T), (void*) (32));
            glEnableVertexAttribArray(2);
        }

    private:
        unsigned int VAO;
        int size;
    };
}

#endif //PALKA_VERTEXARRAYOBJECT_H

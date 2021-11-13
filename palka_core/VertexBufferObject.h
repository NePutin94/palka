//
// Created by NePutin on 9/28/2021.
//

#ifndef PALKA_VERTEXOBJECTBUFFER_H
#define PALKA_VERTEXOBJECTBUFFER_H

#include "BufferObject.h"
#include "VertexData.h"
#include <glad/gl.h>

namespace palka
{
    class VertexBufferObject : public BufferObject
    {
    public:
        VertexBufferObject()
        {
            bufferType = VBO;
        }
        VertexBufferObject(BufferType t)
        {
            bufferType = t;
        }

        template<class T>
        void setData(T* data, int data_size, void* start)
        {
            glBindBuffer(BufferTypeToGl(), bufferID);
            if(this->data_size < data_size)
            {
                this->data_size = data_size;
                glBufferData(BufferTypeToGl(), this->data_size, NULL, BufferRenderTypeToGl());
            }
            glBufferSubData(BufferTypeToGl(), 0, data_size, start);
            // glBindBuffer(BufferTypeToGl(), 0);
        }
    };
}

#endif //PALKA_VERTEXOBJECTBUFFER_H

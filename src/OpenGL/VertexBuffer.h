#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "Utility.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;

public:
    // size is in bytes 
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
    void SetBufferData(const void* data, unsigned int size) const;
    void SetBufferSubData(const void* data, unsigned int offset, unsigned int size) const;
};

#endif
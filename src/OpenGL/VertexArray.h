#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Utility.h"
#include <iostream>

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void UnBind() const;
};

#endif
#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "Utility.h"
#include <memory>
#include <VertexArray.h>

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    std::shared_ptr<VertexArray> m_Va;

public:
    IndexBuffer(const unsigned int* data, unsigned int count, std::shared_ptr<VertexArray> vao = nullptr);
    ~IndexBuffer();


    void SetIndexBuffer(const unsigned int* data, unsigned int count);
    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif
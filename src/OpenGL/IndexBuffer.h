#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#include "Utility.h"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();


    void SetIndexBuffer(const unsigned int* data, unsigned int count);
    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() const { return m_Count; }
};

#endif
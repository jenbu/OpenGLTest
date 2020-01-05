#pragma once
#include <vector>
#include "Utility.h"
#include <iostream>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count)
    {
        //static_assert(false);
    }



    inline const std::vector<VertexBufferElement> GetElements() const { return m_elements; }
    inline unsigned int GetStride() const { return m_Stride;}
};

//GCC does not allow explicit specialization of member templates, only VC++ does, husk på inline!
template<>
inline void VertexBufferLayout::Push <float> (unsigned int count)
{
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
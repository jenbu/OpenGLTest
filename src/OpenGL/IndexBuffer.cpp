#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    std::cout << "IndexBuffer currently bound: " << m_RendererID << std::endl;

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::SetIndexBuffer(const unsigned int* data, unsigned int count)
{
    std::cout << "SetIndexBuffer" << std::endl;
    m_Count = count;
    Bind();
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW))
    UnBind();
}

void IndexBuffer::Bind() const
{
    //std::cout << "IndexBuffer currently bound: " << m_RendererID << std::endl;
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

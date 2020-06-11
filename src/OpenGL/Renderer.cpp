#include "Renderer.h"


void Renderer::Clear() const
{
    GLCall(glClear( GL_COLOR_BUFFER_BIT ));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); //second arg is the number of INDICESE
    //shader.UnBind();
    //va.UnBind();
}

void Renderer::DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_LINES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawInRange(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int offset, unsigned int indexsize) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, indexsize, GL_UNSIGNED_INT, (void*)(offset*sizeof(unsigned int))));
}
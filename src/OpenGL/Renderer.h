#ifndef RENDERER_H
#define RENDERER_H
#include "Utility.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void DrawInRange(const VertexArray& va, const IndexBuffer& ib, const Shader& shader,
                     unsigned int offset, unsigned int indexsize) const;
};

#endif
#ifndef TESTLINES_H
#define TESTLINES_H

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"

#include <memory>

namespace test
{
    class TestLines : public Test
    {

    public:
        TestLines();
        ~TestLines();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        VertexArray m_VAO;
        IndexBuffer m_IndexBuffer;
        Shader m_Shader;

    };

}

#endif
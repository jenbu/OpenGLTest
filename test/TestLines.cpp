#include "TestLines.h"

namespace test
{
    TestLines::TestLines()
    : m_Shader("res/basic_color.shader")
    {
        float positions[] = {
            0.0, 0.0,
            0.5, 0.0,
            0.5, 0.5,
    
            0.0, 0.0,
            0.0, 0.5,
            -0.5, 0.5,
    
            0.0, 0.0,
            -0.5, 0.0,
            -0.5, -0.5,

            0.0, 0.0,
            0.0, -0.5,
            0.5, -0.5,
        };

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2);

        m_VAO.AddBuffer(*m_VertexBuffer, layout);

        m_Shader.Bind();

        


    }

    TestLines::~TestLines()
    {

    }

    void TestLines::OnUpdate(float deltaTime)
    {

    }

    void TestLines::OnRender()
    {

    }

    void TestLines::OnImGuiRender()
    {

    }

}

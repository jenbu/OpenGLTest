#include "TestRectangle2D.h"

namespace test
{
    TestRectangle2D::TestRectangle2D()
    : m_Colors{ 1.0f, 1.0f, 1.0f, 1.0f },
      m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
      m_Translation(200, 200, 0), m_Rotation(0.5f)
    {

        float position[] = {
            -50.0f,  50.0f,
             50.0f,  50.0f,
            -50.0f, -50.0f,
             50.0f, -50.0f
        };

        unsigned int indices[]{
            0, 2, 3,
            3, 1, 0
        };

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(position, sizeof(position));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));
        
        m_Shader = std::make_unique<Shader>("res/basic_color.shader");
        m_Shader->Bind();


        m_VAO->UnBind();
        m_IndexBuffer->UnBind();
        m_VertexBuffer->UnBind();
        m_Shader->UnBind();
    }

    TestRectangle2D::~TestRectangle2D()
    {

    }

    void TestRectangle2D::OnUpdate(float deltaTime)
    {
    }

    void TestRectangle2D::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    }

    void TestRectangle2D::OnImGuiRender()
    {
        Renderer renderer;

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation)*glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", m_Colors[0], m_Colors[1], m_Colors[2], m_Colors[3]);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

        ImGui::ColorEdit4("Clear Color", m_Colors);
        ImGui::SliderFloat3("Translation A", &m_Translation.x, 0.0f, 960.0f);
        ImGui::SliderFloat("Rotation", &m_Rotation, 0.0f, 3.14f);

    }

}

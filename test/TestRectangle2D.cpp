#include "TestRectangle2D.h"

int RectangleObject::m_RectCount = 0;

namespace test
{

    TestRectangle2D::TestRectangle2D()
    : m_Colors{ 1.0f, 1.0f, 1.0f, 1.0f },
      m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
      m_TranslationA(200, 200, 0), m_TranslationB(450, 200, 0), 
      m_RotationA(0.5f), m_RotationB(0.0f)
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

        
        RectangleObject rectA(300, 300), rectB(400, 400);
        m_Rectangles.push_back(rectA);
        m_Rectangles.push_back(rectB);
        m_CurrentRectName = rectA.GetName();
        m_RectIter = m_Rectangles.begin();

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

        ImGui::Text("Mouse PosX: %f, PosY: %f", mouseXPos, mouseYPos);

        if(ImGui::SmallButton(m_CurrentRectName.c_str()))
        {
            if(++m_RectIter == m_Rectangles.end())
                m_RectIter = m_Rectangles.begin();

            m_CurrentRectName = m_RectIter->GetName();
        }

        if(ImGui::Button("Add Square"))
        {
            m_Rectangles.push_back(RectangleObject(500, 500));
            m_RectIter = m_Rectangles.begin();
        }


        for(auto& rect: m_Rectangles)
        {
            glm::vec3* translation = rect.GetTranslation();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), *translation)*glm::rotate(glm::mat4(1.0f), *rect.GetRotationPtr(), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 mvp = m_Proj * m_View * model;
            float* colors = rect.GetColors();
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", colors[0], colors[1], colors[2], colors[3]);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        

        ImGui::ColorEdit4("Rectangle Color", m_RectIter->GetColors());
        ImGui::SliderFloat3(m_RectIter->GetName().c_str(), &m_RectIter->GetTranslation()->x, 0.0f, 960.0f);
        
        ImGui::SliderFloat("Rotation",  m_RectIter->GetRotationPtr(), 0.0f, 3.14f);
        
            

    }

}

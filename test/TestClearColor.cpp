#include "TestClearColor.h"

namespace test {
    
    TestClearColor::TestClearColor()
    : m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f },
      m_Proj(glm::ortho(0.0f, (float)ResolutionWidth, 0.0f, (float)ResolutionHeight, -1.0f, 1.0f))

    {
        m_objectHandler = new ObjectHandler();
        //m_objectHandler->AddObject<RectangleObject>(glm::vec3(400, 500, 0), glm::vec3(0, 0, 0), (float)150, (float)50);
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(200, 500, 0), glm::vec3(0, 0, 0), (float)50, (float)50);
        //m_objectHandler->AddObject<RectangleObject>(glm::vec3(600, 500, 0), glm::vec3(0, 0, 0), (float)50, (float)50);
        m_objectHandler->AddObject<RectangleObject>(glm::vec3(600, 100, 0), glm::vec3(0, 0, 0), (float)100, (float)150);

        m_objectHandler->AddObject<CircleObject>(glm::vec3(600, 200, 0), glm::vec3(0, 0, 0), 40.0f, (unsigned int)6);
        m_objectHandler->AddObject<CircleObject>(glm::vec3(400, 200, 0), glm::vec3(0, 0, 0), 120.0f, (unsigned int)47);
        //m_objectHandler->AddObject<CircleObject>(glm::vec3(100, 200, 0), glm::vec3(0, 0, 0), 80.0f, (unsigned int)12);


        m_Objects = m_objectHandler->GetObjectsData();
        m_VertexData = m_objectHandler->GetVertexData();

        for(int k = 0; k < m_VertexData.VertexPosition.size(); k++)
        std::cout << m_VertexData.VertexPosition[k] << " ";
        std::cout << std::endl;

        for(int k = 0; k < m_VertexData.VertexIndices.size(); k++)
        std::cout << m_VertexData.VertexIndices[k] << " ";
        std::cout << std::endl;

        /*for(int k = 0; k < m_VertexData.ObjectIndexOffset.size(); k++)
        std::cout << m_VertexData.ObjectIndexOffset[k] << " ";
        std::cout << std::endl;*/

        std::cout << "m_VertexData.VertexPosition.size(): " << m_VertexData.VertexPosition.size()
                  << "m_VertexData.VertexIndices.size(): "  << m_VertexData.VertexIndices.size() << std::endl;

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
        m_Shader = std::make_unique<Shader>("res/basic_color.shader"); 
        m_Shader->Bind();
    }

    TestClearColor::~TestClearColor()
    {

    }

    void TestClearColor::OnUpdate(float deltaTime)
    {

    }

    void TestClearColor::OnRender()
    {
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestClearColor::OnImGuiRender()
    {
        //ImGui::ColorEdit4("Clear Color", m_ClearColor);
        for(int i = 0; i < m_objectHandler->GetObjectCount(); i++)
        {
            //std::cout << m_Objects[i]->GetIndicesSize() << std::endl;
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_Objects[i]->GetIndicesOffset(), m_Objects[i]->GetIndicesSize());

        }
    }


}
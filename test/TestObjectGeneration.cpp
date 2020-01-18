#include "TestObjectGeneration.h"

namespace test
{
    TestObjectGeneration::TestObjectGeneration()
    :   m_Proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), m_ToggleGravity(false)
    {
        m_VAO = std::make_unique<VertexArray>();

        RectangleObject rectA(600, 500, 0, 100, 100, 200);
        m_ObjectsData = rectA.GetObjectData();

        RectangleObject rectB(100, 200, 0, 50, 200, 70);
        m_ObjectsData = rectB.GetObjectData();
        RectangleObject rectC(400, 50, 0, 200, 100, 100);
        m_ObjectsData = rectC.GetObjectData();

        std::cout << m_ObjectsData.ObjectIndexOffset[0] << std::endl;
        for(int i = 0; i < m_ObjectsData.ObjectIndexOffset.size(); i++)
            std::cout << m_ObjectsData.ObjectIndexOffset[i] << " ";
        std::cout << std::endl;

        for(int i = 0; i < m_ObjectsData.indices.size(); i++)
            std::cout << m_ObjectsData.indices[i] << " ";

        for(int i = 0; i < m_ObjectsData.position.size(); i++)
            std::cout << m_ObjectsData.position[i] << " ";

        m_VertexBuffer = std::make_unique<VertexBuffer>(&m_ObjectsData.position[0], m_ObjectsData.position.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(&m_ObjectsData.indices[0], m_ObjectsData.indices.size());

        m_Shader = std::make_unique<Shader>("res/basic_color.shader");
        m_Shader->Bind();
    }

    TestObjectGeneration::~TestObjectGeneration()
    {

    }

    void TestObjectGeneration::OnUpdate(float deltaTime)
    {

    }
    
    void TestObjectGeneration::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    }

    void TestObjectGeneration::OnImGuiRender()
    {


        if(ImGui::Button("Toggle Gravity"))
        {
            m_ToggleGravity != m_ToggleGravity;
        }
        
        for(int i = 0; i < m_ObjectsData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_ObjectsData.trans[i].vec);
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_ObjectsData.ObjectIndexOffset[i]);

        }

        
        //ImGui::Text()
        ImGui::SliderFloat3("Translation A", &m_ObjectsData.trans[0].vec.x, 0.0f, 1280.0f);

    }
}

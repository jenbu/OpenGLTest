#include "TestObjectGeneration.h"

namespace test
{
    TestObjectGeneration::TestObjectGeneration()
    :   m_Proj(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), m_ToggleGravity(false)
    {
        m_ObjectHandlerInstance = ObjectHandler::GetInstance();

        m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(100, 200, 0), 50, 50);
        //m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(100, 50, 0), 50, 200);
        m_Objects = m_ObjectHandlerInstance->GetObjectsData();
        m_VertexData = m_ObjectHandlerInstance->GetVertexData();

        std::cout << m_VertexData.VertexPosition.size() << std::endl;
        for(int i = 0; i < m_VertexData.VertexPosition.size(); i++)
        {
            std::cout << m_VertexData.VertexPosition[i] << std::endl;
        }

        std::cout << m_VertexData.VertexIndices.size() << std::endl;
        for(int i = 0; i < m_VertexData.VertexIndices.size(); i++)
        {
            std::cout << m_VertexData.VertexIndices[i] << std::endl;
        }

        std::cout << "ObjectIndexOffset size: "<<m_VertexData.ObjectIndexOffset.size() << " value " << m_VertexData.ObjectIndexOffset[0] << std::endl;

        std::cout << m_VertexData.VertexIndices.size() << std::endl;
        
        std::cout << m_Objects[0]->GetObjectPosVelAcc().PosVec.x << std::endl;
        std::cout << m_Objects[0]->GetObjectPosVelAcc().PosVec.x << std::endl;
        std::cout << m_Objects[0]->GetObjectPosVelAcc().PosVec.y << std::endl;
        std::cout << m_Objects[0]->GetObjectPosVelAcc().PosVec.z << std::endl;
        

        m_VAO = std::make_unique<VertexArray>();

        /*RectangleObject rectA(600, 500, 0, 100, 100, 200);
        m_ObjectsData = rectA.GetObjectData();

        RectangleObject rectB(100, 200, 0, 50, 200, 70);
        m_ObjectsData = rectB.GetObjectData();
        RectangleObject rectC(400, 50, 0, 200, 100, 100);
        m_ObjectsData = rectC.GetObjectData();
*/
        m_VertexBuffer = std::make_unique<VertexBuffer>(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

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
        
        for(int i = 0; i < m_VertexData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetObjectPosVelAcc().PosVec);
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_VertexData.ObjectIndexOffset[i]);

        }

        //m_Objects[0]->GetObjectPosVelAcc().PosVec.x
        //ImGui::Text()
        //ImGui::SliderFloat3("Translation A", &m_Objects[0]->GetObjectPosVelAcc().PosVec.x, 0.0f, 1280.0f);

    }
}

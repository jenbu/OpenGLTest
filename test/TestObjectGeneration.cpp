#include "TestObjectGeneration.h"

const int RESOLUTION_WIDTH = 1200;
const int RESOLUTION_HEIGHT = 720;


namespace test
{
    TestObjectGeneration::TestObjectGeneration()
    :   m_Proj(glm::ortho(0.0f, (float)RESOLUTION_WIDTH, 0.0f, (float)RESOLUTION_HEIGHT, -1.0f, 1.0f)), m_ToggleGravity(false),
        m_Physics(NewtonianPhysics::GetInstance())
    {
        m_ObjectHandlerInstance = ObjectHandler::GetInstance();
        m_Physics->SetBounds(RESOLUTION_WIDTH, 0, RESOLUTION_HEIGHT, 0); 
        m_Physics->setDeltaT(0.08);

        m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(400, 600, 0), glm::vec3(10, 0, 0), 150, 150);
        m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(500, 300, 0), glm::vec3(30, 0, 0), 100, 100);
        //m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(700, 100, 0), 200, 200);
        
        m_Objects = m_ObjectHandlerInstance->GetObjectsData();
        m_VertexData = m_ObjectHandlerInstance->GetVertexData();

        std::cout << "objects size: " << m_Objects.size() << std::endl;
        m_Physics->Calculate(m_Objects);
        
        m_ObjectHandlerInstance->PrintObjectsName();

        m_VAO = std::make_unique<VertexArray>();
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


        if(ImGui::Button("Add Object") && !m_ToggleGravity)
        {
            /*m_ToggleGravity != m_ToggleGravity;
            m_ObjectHandlerInstance->AddObject<RectangleObject>(glm::vec3(700, 300, 0), 40, 70);
            m_Objects = m_ObjectHandlerInstance->GetObjectsData();
            m_VertexData = m_ObjectHandlerInstance->GetVertexData();
            m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
            m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());*/ 
        }
        m_Physics->Calculate(m_Objects);
        
        for(int i = 0; i < m_VertexData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_VertexData.ObjectIndexOffset[i]);

        }

        //m_Objects[0]->GetObjectPosVelAcc().PosVec.x
        //ImGui::Text()
        glm::vec3 posvec = m_Objects[0]->GetPosition();
        ImGui::SliderFloat3("Translation A", &posvec.x, 0.0f, 1280.0f);
        m_Objects[0]->SetObjectPosVelAcc(posvec, glm::vec3(0,0,0), glm::vec3(0,0,0));
        glm::vec3 posvec2 = m_Objects[1]->GetPosition();
        ImGui::SliderFloat3("Translation B", &posvec2.x, 0.0f, 1280.0f);
        m_Objects[1]->SetObjectPosVelAcc(posvec2, glm::vec3(0,0,0), glm::vec3(0,0,0));
        
    }
}

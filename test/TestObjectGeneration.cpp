#include "TestObjectGeneration.h"


namespace test
{
    TestObjectGeneration::TestObjectGeneration()
    :   m_Proj(glm::ortho(0.0f, (float)ResolutionWidth, 0.0f, (float)ResolutionHeight, -1.0f, 1.0f)),
        m_Physics(NewtonianPhysics::GetInstance()), m_NewObjMenu(false), m_NewRectPos({ 0, 0, 0 }), m_NewRectSize({ 0, 0 })
    {
        m_ObjectHandlerInstance = ObjectHandler::GetInstance();

        m_TimeStep = 0.03;
        m_Physics->setDeltaT(m_TimeStep);
        m_Physics->enablePhysics(true);

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
        DebugMenu();

        m_Physics->Calculate(m_Objects);
        
        for(int i = 0; i < m_VertexData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_VertexData.ObjectIndexOffset[i]);

        }

        
    }

    void TestObjectGeneration::DebugMenu()
    {
        if(m_NewObjMenu)
            NewObjectMenu();
        else if(ImGui::Button("New Object"))
            m_NewObjMenu = true;



        if(ImGui::Button("Enable/Disable Physics"))
        {
            if(m_Physics->GetPhysicsEnabled())
                m_Physics->enablePhysics(false);
            else
                m_Physics->enablePhysics(true);
        }

        if(ImGui::InputDouble("TimeStep", &m_TimeStep))
        {
            std::cout << "timestep" << std::endl;
        }

        if(ImGui::Button("Activate Timestep"))
            m_Physics->setDeltaT(m_TimeStep);


        if(!m_Physics->GetPhysicsEnabled())
        {
            glm::vec3 posvec = m_Objects[0]->GetPosition();
            ImGui::SliderFloat3("Translation A", &posvec.x, 0.0f, 1280.0f);
            m_Objects[0]->SetObjectPosVelAcc(posvec, glm::vec3(0,0,0), glm::vec3(0,0,0));
            glm::vec3 posvec2 = m_Objects[1]->GetPosition();
            ImGui::SliderFloat3("Translation B", &posvec2.x, 0.0f, 1280.0f);
            m_Objects[1]->SetObjectPosVelAcc(posvec2, glm::vec3(0,0,0), glm::vec3(0,0,0));
        }
            
    }

    void TestObjectGeneration::NewObjectMenu()
    {
        if(ImGui::Button("Exit"))
            m_NewObjMenu = false;


        ImGui::InputInt3("Position", m_NewRectPos);
        ImGui::InputInt2("Size", m_NewRectSize);

        if(ImGui::Button("Add Object"))
        {
            glm::vec3 posVec3(m_NewRectPos[0], m_NewRectPos[1], m_NewRectPos[2]);
            m_ObjectHandlerInstance->AddObject<RectangleObject>(posVec3, glm::vec3(0,0,0), m_NewRectSize[0], m_NewRectSize[1]);
            m_Objects = m_ObjectHandlerInstance->GetObjectsData();
            m_VertexData = m_ObjectHandlerInstance->GetVertexData();
            m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
            m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());

            m_NewRectPos[0] = 0; m_NewRectPos[1] = 0; m_NewRectPos[2] = 0;
            m_NewRectSize[0] = 0; m_NewRectSize[1] = 0;
        }
    }
}

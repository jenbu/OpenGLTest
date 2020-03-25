#include "TestObjectGeneration.h"


   
namespace test
{
    TestObjectGeneration::TestObjectGeneration()
    :   m_Proj(glm::ortho(0.0f, (float)ResolutionWidth, 0.0f, (float)ResolutionHeight, -1.0f, 1.0f)),
        m_Physics(NewtonianPhysics::GetInstance()), m_NewObjMenu(false), m_NewRectPos({ 0, 0, 0 }), m_NewRectSize({ 0, 0 }),
        m_TogglePhysics(false), m_TimeStepApply(false), m_NewObject(false),
        m_NewObjCoords(glm::ivec3(0,0,0)), m_NewRectProps(glm::ivec2(0,0)), m_CursPos(glm::dvec2(0.0, 0.0))
    {
        m_ObjectHandler = new ObjectHandler();

        m_TimeStep = 0.03;
        m_Physics->setDeltaT(m_TimeStep);
        m_Physics->enablePhysics(true);
        m_Physics->setCursorData(&m_CursPos);

        m_ObjectHandler->AddObject<RectangleObject>(glm::vec3(400, 600, 0), glm::vec3(10, 0, 0), 150, 150);
        m_ObjectHandler->AddObject<RectangleObject>(glm::vec3(500, 300, 0), glm::vec3(30, 0, 0), 100, 100);
        //m_ObjectHandler->AddObject<RectangleObject>(glm::vec3(700, 100, 0), 200, 200);
        
        m_Objects = m_ObjectHandler->GetObjectsData();
        m_ObjsPos = m_ObjectHandler->GetObjectsPos();
        m_VertexData = m_ObjectHandler->GetVertexData();

        std::cout << "objects size: " << m_Objects.size() << std::endl;
        m_Physics->Calculate(m_Objects);
        
        m_ObjectHandler->PrintObjectsName();

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
        m_Shader = std::make_unique<Shader>("res/basic_color.shader"); 
        m_Shader->Bind();

        MenuInit();
    }

    TestObjectGeneration::~TestObjectGeneration()
    {
        delete m_ObjectHandler, m_Menu, m_Submenu;
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

        m_Physics->Calculate(m_Objects);
        MenuEvents();

        
        for(int i = 0; i < m_VertexData.ObjectIndexOffset.size(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_Proj* glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_VertexData.ObjectIndexOffset[i]);

        }

        
    }

    void TestObjectGeneration::MenuInit()
    {
            m_Menu = new ImGuiMenu("TestMeny");
            ImGuiSubMenu* globalPropMenu = new ImGuiSubMenu("Global Properties");
            globalPropMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("EnableDisable Physics", &m_TogglePhysics));
            globalPropMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::InputDouble>("TimeStep", &m_TimeStep));
            globalPropMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("Apply Timestep", &m_TimeStepApply));
            //ImGuiSubMenu *Submenu2 = new ImGuiSubMenu("Testing");
                    
            ImGuiSubMenu *newObjectMenu = new ImGuiSubMenu("New object");
            newObjectMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::InputInt3>("Coords", &m_NewObjCoords));
            newObjectMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::InputInt2>("Width, Height", &m_NewRectProps));
            newObjectMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("Add new Rect", &m_NewObject));

            ImGuiSubMenu *objectMenu = new ImGuiSubMenu("Objects");
            ImGuiSubMenu *objectPosMenu = new ImGuiSubMenu("Object position", true);

            objectMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("New Object", NULL), newObjectMenu);
            objectMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("Object Positions", NULL), objectPosMenu);
            
            
            objectPosMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::Button>("Apply changes", &m_ApplyPosChange));
            objectPosMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::DragFloat3>("test 1", &m_ObjsPos[0]));
            objectPosMenu->SubMenuAddElement(new ImGuiMenuElement<MenuSubElement::DragFloat3>("test 2", &m_ObjsPos[1]));
            
            m_Menu->AddSubMenu(globalPropMenu);
            //m_Menu->AddSubMenu(Submenu2);
            m_Menu->AddSubMenu(objectMenu);
            m_Menu->AddSubMenu(objectPosMenu);
    }

    void TestObjectGeneration::MenuEvents()
    {
        m_Menu->MenuDraw();

        if(m_NewObject)
        {
            if(m_NewRectProps.x > 1 && m_NewRectProps.y > 1)
            {
                m_ObjectHandler->AddObject<RectangleObject>(m_NewObjCoords, glm::vec3(0,0,0), m_NewRectProps.x, m_NewRectProps.y);
                m_Objects = m_ObjectHandler->GetObjectsData();
                m_VertexData = m_ObjectHandler->GetVertexData();
                m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
                m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
            }
            else
            {
                std::cout << "invalid width height value" << std::endl;
            }
            std::cout << "new obj" << std::endl;

        }
        
        if(m_TogglePhysics)
        {
            m_Physics->enablePhysics(!m_Physics->GetPhysicsEnabled());
            //for(int i = 0; i < m_Objects.size(); i++)
            //    m_Objects[i]->SetObjectPosVelAcc(m_ObjsPos[i], glm::vec3(0,0,0), glm::vec3(0,0,0));
        } 
        
        if(m_TimeStepApply)
            m_Physics->setDeltaT(m_TimeStep);
    }
}


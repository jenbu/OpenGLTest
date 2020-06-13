#include "TestFreetype.h"

namespace test
{
    TestFreetype::TestFreetype()
    : m_ProjMatrix(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f))
    {


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if(InitializeFT())
            std::cout << "Error initializing Freetype!" << std::endl;
        
    }

    TestFreetype::~TestFreetype()
    {
        
    }

    int TestFreetype::InitializeFT()
    {
        float vertices[] = {
            100,     200,            
            100,     100,
            200,     100,
            200,     200    
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        m_ObjHandler = std::make_unique<ObjectHandler>();
        m_ObjHandler->AddObject<RectangleObject>(glm::vec3(300, 400, 0), glm::vec3(0, 0, 0), (float)200, (float)100);
        //m_ObjHandler->AddObject<RectangleObject>(glm::vec3(400, 100, 0), glm::vec3(0, 0, 0), (float)200, (float)100);
        //m_ObjHandler->AddObject<RectangleObject>(glm::vec3(400, 400, 0), glm::vec3(0, 0, 0), (float)100, (float)100);
        //m_ObjHandler->AddObject<CircleObject>(glm::vec3(600, 400, 0), glm::vec3(0, 0, 0), (float)30, (unsigned int)30);

        std::vector<float> VertexPos = m_ObjHandler->GetVertexData().VertexPosition;
        std::vector<unsigned int> Indeces = m_ObjHandler->GetVertexData().VertexIndices;
        std::cout << VertexPos.size() << " " << Indeces.size()<< std::endl;
        m_VertexBuffer = std::make_shared<VertexBuffer>(&VertexPos[0], VertexPos.size()*sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2); //Vertex coordinates
        std::cout << sizeof(indices)/sizeof(unsigned int) << std::endl;
        m_VAO = std::make_shared<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBufferTest = std::make_shared<IndexBuffer>(&Indeces[0], Indeces.size(), m_VAO);
        m_Shader = std::make_shared<Shader>("res/basic_color.shader"); 

        //m_IndexBufferTest->SetIndexBuffer(indices, sizeof(indices)/sizeof(unsigned int));
        
        m_Renderer = std::make_shared<Renderer>();

        m_Text = std::make_unique<TextFreetype>(80, m_ProjMatrix);
        m_Text->AddText("Score: 0", 1, 200, 200, glm::vec3(1.0f, 0.0f, 1.0f));

        return 0;
    }

    void TestFreetype::Reset()
    {        
        m_ObjHandler->Clear();

        m_ObjHandler->AddObject<RectangleObject>(glm::vec3(400, 100, 0), glm::vec3(0, 0, 0), (float)50, (float)50);

        std::vector<float> VertexPos = m_ObjHandler->GetVertexData().VertexPosition;
        std::vector<unsigned int> Indeces = m_ObjHandler->GetVertexData().VertexIndices;
        std::cout << VertexPos.size() << " " << Indeces.size()<< std::endl;
        m_VertexBuffer->SetBufferData(&VertexPos[0], VertexPos.size()*sizeof(float));

        m_IndexBufferTest->SetIndexBuffer(&Indeces[0], Indeces.size());//nullptr, 0);
    }


    void TestFreetype::OnUpdate(float deltaTime)
    {

    }

    void TestFreetype::OnRender()
    {
    }

    void TestFreetype::OnImGuiRender()
    {
        static int inc = 0;

        //std::cout << ++inc << std::endl;

        if(++inc > 100)
        {
            inc = 0;
            Reset();
        }

        std::vector<BaseObject*> objs = m_ObjHandler->GetObjectsData();
        for(int i = 0; i < m_ObjHandler->GetObjectCount(); i++)
        {
            glm::mat4 mvp = glm::mat4(1.0f)* m_ProjMatrix* glm::translate(glm::mat4(1.0f), objs[i]->GetPosition());

            //m_ProjMatrix = m_ProjMatrix*glm::translate(glm::mat4f(1.0f),);
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

            m_Renderer->Draw(*m_VAO, *m_IndexBufferTest, *m_Shader);

        }

        std::ostringstream ss;
        static int i = 0;
        std::string score;
        i++;
        ss << "Score: " << i;
        m_Text->SetText(ss.str(), 1);
        m_Text->Render();

        std::cout << inc << std::endl;

        


        //m_Shader->UnBind();
        //m_VertexBuffer->UnBind();
        //m_IndexBuffer->UnBind();
        //m_VAO->UnBind();
        

    }

}
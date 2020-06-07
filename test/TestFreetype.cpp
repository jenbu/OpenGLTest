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

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        m_VertexBuffer = std::make_shared<VertexBuffer>(nullptr, 0);
        VertexBufferLayout layout;
        layout.Push<float>(2); //Vertex coordinates
        layout.Push<float>(2); //Texture coordinates

        m_VAO = std::make_shared<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        //m_IndexBuffer = std::make_shared<IndexBuffer>(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
        m_Shader = std::make_shared<Shader>("res/freetype_shader.shader"); 
        m_Shader->Bind();

        m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));
        
        m_Renderer = std::make_shared<Renderer>();
        m_Text = std::make_unique<TextFreetype>(m_VertexBuffer, m_IndexBuffer, m_Renderer, m_Shader, m_VAO, m_ProjMatrix);
        m_Text->SetText("ABCD", 1, 200, 200, glm::vec3(1.0f, 0.0f, 1.0f));
        m_Text->SetText("AdfsD", 0, 300, 100, glm::vec3(1.0f, 0.0f, 0.0f));
        m_Text->SetText("ABCDefgh", 1, 200, 200, glm::vec3(1.0f, 0.0f, 1.0f));

        return 0;
    }


    void TestFreetype::OnUpdate(float deltaTime)
    {

    }

    void TestFreetype::OnRender()
    {
    }

    void TestFreetype::OnImGuiRender()
    {
        m_Text->Render();
    }

}
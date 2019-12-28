#include "TestTexture2D.h"


namespace test {
    
    TestTexture2D::TestTexture2D()
    : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
      m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
    {
        static const GLfloat g_vertex_buffer_data[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,
        50.0f, -50.0f, 1.0f, 0.0f,
        50.0f,  50.0f, 0.1f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f 
        //1.0f, 1.0f
        };

        unsigned int indices[]{
            0, 1, 2,
            2, 3, 0//,
        // 4, 1, 2
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));

        m_Shader = std::make_unique<Shader>("res/basic.shader");
        m_Shader->Bind();

        m_Texture = std::make_unique<Texture>("res/Textures/cherno.png");
        m_Texture->Bind(0);
        m_Shader->SetUniform1i("u_Texture", 0);
        
        m_VAO->UnBind();
        m_Shader->UnBind();
        m_VertexBuffer->UnBind();
        m_IndexBuffer->UnBind();
    }

    TestTexture2D::~TestTexture2D()
    {

    }

    void TestTexture2D::OnUpdate(float deltaTime)
    {

    }

    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void TestTexture2D::OnImGuiRender()
    {
        Renderer renderer;

        m_Texture->Bind(0);

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }


}
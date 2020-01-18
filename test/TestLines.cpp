#include "TestLines.h"

namespace test
{
    TestLines::TestLines()
    : m_Rotation(M_PI_2), m_Proj(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f)),
      m_AdjustPoint(0.0f)
    
    {
        float positions[] = {
             0.0, 0.0,  //0
             0.5, 0.0,  //1
             0.0, 0.5,  //2
             0.5, 0.5,  //3
            -0.5, 0.0,  //4
             0.0, -0.5, //5
            -0.5, 0.5,  //6
            0.5, -0.5,  //7
            -0.5, -0.5, //8
        };

        unsigned int indices[] = {
            6, 2,
            2, 5
        };

        m_PointCount = sizeof(positions)/(2*sizeof(float));

        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

        m_Layout.Push<float>(2);

        m_VAO.AddBuffer(*m_VertexBuffer, m_Layout);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices)/sizeof(unsigned int));

        m_Shader = std::make_unique<Shader>("res/basic_color.shader");
        m_Shader->Bind();

        m_VAO.UnBind();
        m_VertexBuffer->UnBind();
        m_IndexBuffer->UnBind();
        m_Shader->UnBind();
        


    }

    TestLines::~TestLines()
    {

    }

    void TestLines::OnUpdate(float deltaTime)
    {

    }

    void TestLines::OnRender()
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    }

    void TestLines::OnImGuiRender()
    {
        Renderer renderer;
        glm::mat3 rotation = Transformation2D(m_Rotation, 0, 0);
        
        glm::mat4 mvp = glm::mat4(rotation[0][0], rotation[0][1], rotation[0][2], 0.0,
                                  rotation[1][0], rotation[1][1], rotation[1][2], 0.0,
                                  rotation[2][0], rotation[2][1], rotation[2][2], 0.0,
                                  0.0          , 0.0          , 0.0          , 1.0);

        mvp *= m_Proj;





        float positions[] = {
             m_AdjustPoint, 0.0,  //0
             0.5, 0.0,  //1
             0.0, 0.5,  //2
             0.5, 0.5,  //3
            -0.5, 0.0,  //4
             0.0, -0.5, //5
            -0.5, 0.5,  //6
            0.5, -0.5,  //7
            -0.5, -0.5, //8
        };
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        m_VAO.AddBuffer(*m_VertexBuffer, m_Layout);
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.DrawLines(m_VAO, *m_IndexBuffer, *m_Shader);

        ImGui::SliderFloat("Rotation",  &m_Rotation, 0.0f, 2*M_PI);
        ImGui::SliderFloat("adjust",  &m_AdjustPoint, 0.0f, 2*M_PI);
    }

}

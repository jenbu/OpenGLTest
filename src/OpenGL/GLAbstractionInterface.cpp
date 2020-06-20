#include "GLAbstractionInterface.h"

GLAbstractionInterface::GLAbstractionInterface(unsigned int res_width, unsigned int res_height)
: m_Proj(glm::ortho(0.0f, (float)res_width, 0.0f, (float)res_height, -1.0f, 1.0f)),
  m_TextCount(0)
{

    m_VAO = std::make_shared<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, 0);
    VertexBufferLayout layout;
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(nullptr, 0, m_VAO);
    m_Shader = std::make_unique<Shader>("res/basic_color.shader"); 

    m_ObjHandler = std::make_unique<ObjectHandler>();
    m_Objects = m_ObjHandler->GetObjectsData();

    m_Text = std::make_unique<TextFreetype>(40, glm::mat4(1.0f)* m_Proj);
}

GLAbstractionInterface::~GLAbstractionInterface()
{
    
}

void GLAbstractionInterface::Test()
{

}

void GLAbstractionInterface::Render()
{
    for(int i = 0; i < m_ObjHandler->GetObjectCount(); i++)
    {
        glm::mat4 mvp = glm::mat4(1.0f)* m_Proj * glm::translate(glm::mat4(1.0f), m_Objects[i]->GetPosition());
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->DrawInRange(*m_VAO, *m_IndexBuffer, *m_Shader, m_Objects[i]->GetIndicesOffset(), m_Objects[i]->GetIndicesSize());
    }

    m_Text->Render();
}

void GLAbstractionInterface::UpdateBuffers()
{
    m_Objects = m_ObjHandler->GetObjectsData();
    m_VertexData = m_ObjHandler->GetVertexData();
    m_VertexBuffer->SetBufferData(&m_VertexData.VertexPosition[0], m_VertexData.VertexPosition.size()*sizeof(float));
    m_IndexBuffer->SetIndexBuffer(&m_VertexData.VertexIndices[0], m_VertexData.VertexIndices.size());
}

int GLAbstractionInterface::AddText(std::string text, unsigned int x, unsigned int y)
{
    m_Text->AddText(text, m_TextCount, x, y, glm::vec3(1.0f, 1.0f, 1.0f));
    return m_TextCount;
}

void GLAbstractionInterface::SetText(unsigned int id, std::string text)
{
    m_Text->SetText(text, id);
}


#ifndef TESTLINES_H
#define TESTLINES_H

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test
{
    class TestLines : public Test
    {

    public:
        TestLines();
        ~TestLines();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        VertexArray m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        VertexBufferLayout m_Layout;

        int m_PointCount;
        float m_Rotation;
        float m_AdjustPoint;
        glm::mat4 m_Proj;

    };

}

#endif
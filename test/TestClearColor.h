#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H

#include "Test.h"
#include "Utility.h"
#include "imgui/imgui.h"

namespace test {
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_ClearColor[4];

        std::vector<BaseObject*> m_Objects;
        VertexData m_VertexData;

        Renderer m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
    };
}

#endif
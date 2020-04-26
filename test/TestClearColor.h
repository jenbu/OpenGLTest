#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H

#include <memory>
#include <vector>

#include "Test.h"
#include "Utility.h"
#include "imgui/imgui.h"
#include "Constants.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ObjectHandler.h"

#include "BaseObject.h"
#include "RectangleObject.h"
#include "CircleObject.h"


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

        glm::mat4 m_Proj;

        ObjectHandler* m_objectHandler;
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
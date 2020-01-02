#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Utility.h"
#include "RectangleObject.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

#include <vector>
#include <memory>


namespace test
{
    class TestRectangle2D : public Test
    {
    public:
        TestRectangle2D();
        ~TestRectangle2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private: 
        float m_Colors[4];
        glm::vec3 m_TranslationA, m_TranslationB;
        glm::mat4 m_Proj, m_View;
        float m_RotationA, m_RotationB;
        std::vector<RectangleObject> m_Rectangles;

        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

    };
}
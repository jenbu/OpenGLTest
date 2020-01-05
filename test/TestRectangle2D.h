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
#include <GLFW/glfw3.h>

#include <vector>
#include <memory>
#include "math.h"

extern std::vector<double> mousePos;

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

        bool detectCursorRectCollision(std::vector<double> mousePos, glm::vec3 pos, float angle);
        inline glm::mat3 Calc2DRotationMat(float angle) { return glm::mat3(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1); };

    private: 
        float m_Colors[4];
        glm::mat4 m_Proj, m_View;
        std::vector<RectangleObject> m_Rectangles;
        std::vector<RectangleObject>::iterator m_RectIter;
        std::string m_CurrentRectName;
        bool toggleWhite;



        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

    };
}
#pragma once

#include <vector>
#include <memory>

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Test.h"
#include "Utility.h"
#include "Constants.h"
#include "RectangleObject.h"
#include "ObjectHandler.h"
#include "InputEventHandler.h"

namespace test
{
    struct GridPos
    {
        int x;
        int y;
    };

    enum CollisionType
    {
        Boundary = 1,
        Snake = 2,
        NoCollision = -1
    };


    class TestSnake : public Test
    {
    public:
        TestSnake();
        ~TestSnake();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void AddBodySquare();
        void SetGridPos(int& x, int& y);
        void KeyEvents();
        void ResetGame();

        CollisionType Collision(int x, int y);
    private:
        unsigned int m_gridPixelSize;
        const unsigned int m_GridNum; 
        std::vector<GridPos> m_SnakePos;

        ObjectHandler* m_objectHandler;
        InputEventHandler* m_InputInstance;

        glm::mat4 m_Proj;
        bool m_Toggle;

        int m_Gridx, m_Gridy;
        unsigned int m_xPixelOffset, m_yPixelOffset;


        std::vector<BaseObject*> m_Objects;
        VertexData m_VertexData;

        Renderer m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
    };



}
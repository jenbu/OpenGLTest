#pragma once

#include <vector>
#include <memory>
#include <time.h>

#include "ft2build.h"
#include FT_FREETYPE_H

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
#include "UDPClass.h"

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

    enum Direction
    {
        Up = 1,
        Down = 2,
        Left = 3,
        Right = 4
    };


    class TestSnake : public Test
    {
    public:
        TestSnake();
        ~TestSnake();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void SetSnakePos(int& x, int& y);
        bool IsEating();
        void EatingConsequence();

        void GameTick();
        void KeyEvents();
        void ResetGame();

        void AddBodySquare();
        CollisionType Collision(int x, int y);
        void SetGridPos(BaseObject* obj, int x, int y);

        void SnakeMsgHandler();

        //void TestFunc();
    private:
        std::vector<GridPos> m_SnakePos;
        GridPos m_FoodPos;
        Direction m_SnakeDirection;

        ObjectHandler* m_objectHandler;
        InputEventHandler* m_InputInstance;
        Communication::UDPClass m_UDP;
        glm::mat4 m_Proj;

        //Timer
        clock_t m_lastTime;
        clock_t m_TickPeriod;

        unsigned int m_gridPixelSize;
        const unsigned int m_GridNum; 
        int m_Gridx, m_Gridy;
        unsigned int m_xPixelOffset, m_yPixelOffset;


        std::vector<BaseObject*> m_Objects;
        BaseObject* m_Food;
        std::vector<RectangleObject*> m_ObjectsRects;
        VertexData m_VertexData;

        Renderer m_Renderer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
    };



}
#pragma once

#include <vector>
#include <memory>
#include <time.h>

#include "Test.h"
#include "Utility.h"
#include "Constants.h"

#include "InputEventHandler.h"
#include "UDPClass.h"
#include "GLAbstractionInterface.h"

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

        void SnakeMsgHandler(char* msg);
        std::vector<bool> GetState();

    private:
        std::unique_ptr<GLAbstractionInterface> m_GLinterface;
        unsigned int m_TextScoreID;
        unsigned int m_Score;
        std::vector<GridPos> m_SnakePos;
        GridPos m_FoodPos;
        Direction m_SnakeDirection;
        std::vector<bool> m_States;

        InputEventHandler* m_InputInstance;
        Communication::UDPClass* m_UDPComm;

        //Timer
        clock_t m_lastTime;
        clock_t m_TickPeriod;
        bool m_GamePaused;

        unsigned int m_gridPixelSize;
        const unsigned int m_GridNum; 
        int m_Gridx, m_Gridy;
        unsigned int m_xPixelOffset, m_yPixelOffset;

        BaseObject* m_Food;
        std::vector<RectangleObject*> m_ObjSnakeBody;
    };



}
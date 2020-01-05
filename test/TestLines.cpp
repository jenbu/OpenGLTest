#include "TestLines.h"

namespace test
{
    TestLines::TestLines()
    {
        float positions[] = {
            0.0, 0.0,
            0.5, 0.0,
            0.5, 0.5,
    
            0.0, 0.0,
            0.0, 0.5,
            -0.5, 0.5,
    
            0.0, 0.0,
            -0.5, 0.0,
            -0.5, -0.5,

            0.0, 0.0,
            0.0, -0.5,
            0.5, -0.5,
        };

        VertexBuffer abc(positions, sizeof(positions));
    }

    TestLines::~TestLines()
    {

    }

    void TestLines::OnUpdate(float deltaTime)
    {

    }

    void TestLines::OnRender()
    {

    }

    void TestLines::OnImGuiRender()
    {

    }

}

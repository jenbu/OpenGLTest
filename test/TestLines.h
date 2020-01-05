#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace test
{
    class TestLines : public Test
    {
    private:
        VertexArray m_VAO;
        VertexBuffer m_VertexBuffer;

    public:
        TestLines();
        ~TestLines();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };

}
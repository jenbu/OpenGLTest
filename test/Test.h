#ifndef TEST_H
#define TEST_H 

#include <functional>
#include <vector>
#include <iostream>

namespace test {
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
        virtual void CursorUpdate(double x, double y) {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTestPointer);

        void OnImGuiRender() override;
        void CursorUpdate(double x, double y) override {};

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registering test " << name << std::endl;
            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}


#endif
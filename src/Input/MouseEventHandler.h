#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>


enum ButtonEvent
{
    LeftBtn    = 0,
    RightBtn   = 1,
    ScrlClkBtn = 2,
    BackBtn    = 3,
    ForwBtn    = 4,
    NoBtn      = -1
};


class MouseEventHandler
{

public:
    static MouseEventHandler* GetInstance();
    void SetCursorPos(int x, int y) { m_CursorPos = glm::ivec2(x, y); }
    glm::ivec2 GetCursorPos() { return m_CursorPos; }
    ButtonEvent GetBtnState();
    void Heisann() { std::cout << "Heisann" << std::endl; }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
    MouseEventHandler();

    static MouseEventHandler* m_instance;

    static int m_CurrentPressedBtn;
    static bool m_BtnToggle;
    glm::ivec2 m_CursorPos;


};
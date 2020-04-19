#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
#include "Constants.h"


enum ButtonEvent
{
    LeftBtn    = 0,
    RightBtn   = 1,
    ScrlClkBtn = 2,
    BackBtn    = 3,
    ForwBtn    = 4,
    NoMouseBtn = -1
};

enum KeyboardEvent
{
    ArrowDown = 264,
    ArrowUp = 265,
    ArrowLeft = 263,
    ArrowRight = 262,
    KeyE = 69,
    NoKeyBtn = -1
};


class InputEventHandler
{

public:
    static InputEventHandler* GetInstance();
    void SetCursorPos(int x, int y) { m_CursorPos = glm::ivec2(x, ResolutionHeight-y); }
    glm::ivec2 GetCursorPos() { return m_CursorPos; }
    ButtonEvent GetBtnState();
    KeyboardEvent GetKeyState();
    void Heisann() { std::cout << "Heisann" << std::endl; }

    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
    InputEventHandler();

    static InputEventHandler* m_instance;
    static int m_CurrentPressedBtn;
    static KeyboardEvent m_CurrentKeyboardBtn, m_PreviousKeyboardBtn;

    bool m_MouseBtnToggle; 
    bool m_Toggle;

    glm::ivec2 m_CursorPos;


};
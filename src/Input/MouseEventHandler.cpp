#include "MouseEventHandler.h"

MouseEventHandler* MouseEventHandler::m_instance = 0;
int MouseEventHandler::m_CurrentPressedBtn = ButtonEvent::NoBtn;
bool MouseEventHandler::m_BtnToggle = false;

MouseEventHandler::MouseEventHandler()

{

}

MouseEventHandler* MouseEventHandler::GetInstance()
{
    if(!m_instance)
        m_instance = new MouseEventHandler;

    return m_instance;
}

ButtonEvent MouseEventHandler::GetBtnState()
{
    //Only return button state at btn press
    if(m_BtnToggle)
    {
        m_BtnToggle = false;
        return (ButtonEvent)m_CurrentPressedBtn;
    }
    return ButtonEvent::NoBtn;
}

void MouseEventHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    std::cout << "MouseButtonCallback, button: " << button <<  std::endl;
    if(action == GLFW_PRESS)
    {
        m_BtnToggle = true;
        m_CurrentPressedBtn = button;
    }
    else //btn released
    {
        m_CurrentPressedBtn = -1;
    }
    
}

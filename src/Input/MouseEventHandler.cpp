#include "MouseEventHandler.h"

MouseEventHandler* MouseEventHandler::m_instance = 0;
int MouseEventHandler::m_CurrentPressedBtn = ButtonEvent::NoBtn;


MouseEventHandler::MouseEventHandler()
: m_MouseBtnToggle(false)
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
    return (ButtonEvent)m_CurrentPressedBtn;
}

void MouseEventHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    //std::cout << "MouseButtonCallback, button: " << button <<  std::endl;
    if(action == GLFW_PRESS)
    {
        //m_MouseBtnToggle = true;
        m_CurrentPressedBtn = button;
    }
    else //btn released
    {
        m_CurrentPressedBtn = -1;
    }
    
}

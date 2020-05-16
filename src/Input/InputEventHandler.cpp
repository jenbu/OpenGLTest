#include "InputEventHandler.h"

InputEventHandler* InputEventHandler::m_instance = 0;
int InputEventHandler::m_CurrentPressedBtn = ButtonEvent::NoMouseBtn;
KeyboardEvent InputEventHandler::m_CurrentKeyboardBtn = KeyboardEvent::NoKeyBtn;
KeyboardEvent InputEventHandler::m_PreviousKeyboardBtn = KeyboardEvent::NoKeyBtn;
//bool InputEventHandler::m_Toggle = false;
InputEventHandler::InputEventHandler()
: m_MouseBtnToggle(false)
{

}

InputEventHandler* InputEventHandler::GetInstance()
{
    if(!m_instance)
        m_instance = new InputEventHandler;

    return m_instance;
}

ButtonEvent InputEventHandler::GetBtnState()
{ 
    return (ButtonEvent)m_CurrentPressedBtn;
}

KeyboardEvent InputEventHandler::GetKeyState()
{
        if((m_CurrentKeyboardBtn != KeyboardEvent::NoKeyBtn) && !m_Toggle)
        {
            //std::cout << "key"<< std::endl;
            m_Toggle = true;
            return m_CurrentKeyboardBtn;
        }
        else if(m_CurrentKeyboardBtn == KeyboardEvent::NoKeyBtn)
        {
            //std::cout << "no key"<< std::endl;
            m_Toggle = false;
            return m_CurrentKeyboardBtn;
        }

    return KeyboardEvent::NoKeyBtn;
}

void InputEventHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
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
    //std::cout << "m_CurrentPressedBtn, button: " << m_CurrentPressedBtn <<  std::endl;
}

void InputEventHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //std::cout << "Key pressed: " << key << std::endl;
    if(action == GLFW_PRESS)
    {
        if(key != m_CurrentKeyboardBtn)
        {
            //std::cout << "Key pressed: " << key << std::endl;

            m_PreviousKeyboardBtn = m_CurrentKeyboardBtn;
            m_CurrentKeyboardBtn = (KeyboardEvent)key;
        }
    }
    else if(action == GLFW_REPEAT)
    {
        m_CurrentKeyboardBtn = KeyboardEvent::NoKeyBtn;
    }
    else
    {
            //std::cout << "Key released: " << key << std::endl;
            //m_PreviousKeyboardBtn = m_CurrentKeyboardBtn;
            m_CurrentKeyboardBtn = KeyboardEvent::NoKeyBtn;
        
    }
    
}

#include "MouseManipulator.h"

MouseManipulator::MouseManipulator()
: m_toggleSelection(2, false)
{
    m_MouseEvents = MouseEventHandler::GetInstance();
    m_Collision = CollisionDetection::GetInstance();

}

void MouseManipulator::Manipulate(std::vector<BaseObject*> objects)
{
    //todo: fikse togglinga
    for(int i = 0; i < objects.size(); i++)
    {
        if(m_Collision->CursorObjectCollision(objects[i], m_MouseEvents->GetCursorPos()))
        {
            if(!m_toggleSelection[i])
            {
                m_toggleSelection[i] = true;
                objects[i]->ToggleObjPhysics();
            }
        }
        else
        {
            m_toggleSelection[i] = false;
        }
        
    }
}
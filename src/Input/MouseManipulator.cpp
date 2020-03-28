#include "MouseManipulator.h"

MouseManipulator::MouseManipulator()
: m_toggleSelection(2, false), m_SelectedObj(nullptr), m_SelectionToggle(false),
  m_EnableDrag(false), m_Dragging(false)
{
    m_MouseEvents = MouseEventHandler::GetInstance();
    m_Collision = CollisionDetection::GetInstance();

}

void MouseManipulator::Manipulate(std::vector<BaseObject*> objects)
{

    //todo: fikse togglinga
    for(int i = 0; i < objects.size(); i++)
    {
        if(ObjectSelection(objects[i]))
        {
            //std::cout << "obj selected" << std::endl;
            m_SelectedObj = objects[i];
            return;
        }
    }

    Drag();
    m_SelectionToggle = false;


    if(m_SelectedObj != NULL)
        std::cout << "Obj " << m_SelectedObj->GetName() << " selected!" << std::endl; 
    else
        std::cout << "No Obj selected" << std::endl;
    

}

bool MouseManipulator::ObjectSelection(BaseObject* obj)
{
    //std::cout << m_MouseEvents->GetBtnState() << std::endl;
    if(ButtonEvent::LeftBtn == m_MouseEvents->GetBtnState())
    {       
    
        if(m_Collision->CursorObjectCollision(obj, m_MouseEvents->GetCursorPos()))
        {
            if(!m_SelectionToggle)
            {
                m_SelectionToggle = true;
                if(m_Dragging)
                {
                    m_Dragging = false;
                }
                else
                {
                    obj->ToggleObjPhysics();
                }
                
                if(m_EnableDrag && !obj->IsPhysEnabled())
                {
                    m_Dragging = true;
                    m_EnableDrag = false;
                    return true;
                }

                m_EnableDrag = true;

            }
            return true;
        }
        else
        {
            if(m_SelectedObj != NULL)
            {
                //m_SelectionToggle = false;
                //std::cout << "Deselected object" << std::endl;
                m_SelectedObj = NULL;
            }
        }

        
        
    }


    return false;
}

void MouseManipulator::Drag()
{
    if(m_SelectedObj != NULL && !m_SelectedObj->IsPhysEnabled())
    {
        glm::vec3 velocity = m_SelectedObj->GetVelocity();
        glm::vec3 acc = m_SelectedObj->GetAcceleration();
        glm::ivec2 curs = m_MouseEvents->GetCursorPos();
        glm::vec3 cursorPos = glm::vec3(curs.x, curs.y, 0);
        
        if(m_Dragging)
        {
            m_SelectedObj->SetObjectPosVelAcc(cursorPos, velocity, acc);
        }
    }

    //if(m_SelectedObj == NULL)
    //    m_EnableDrag = false;
}
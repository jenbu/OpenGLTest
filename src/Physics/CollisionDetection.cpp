#include "CollisionDetection.h"

CollisionDetection* CollisionDetection::m_Instance = 0; 

CollisionDetection::CollisionDetection()
{

}

CollisionDetection::~CollisionDetection()
{

}

CollisionDetection* CollisionDetection::GetInstance()
{
    if(m_Instance == 0)
    {
        m_Instance = new CollisionDetection;
    }

    return m_Instance;
}

bool CollisionDetection::InterCollision(std::vector<BaseObject*>  objects, BaseObject* currentobj)
{
    for(std::vector<BaseObject*>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        if(*it == currentobj)
        {
            //std::cout << "Same obj" << std::endl;
            continue;
        }
        
        glm::vec3 currentPos = currentobj->GetPosition();
        glm::vec3 iterPos = (*it)->GetPosition();

        //assumption that currentObj is rect too
        if(currentobj->GetType() == Rect && (*it)->GetType() == Rect)
        {
            RectangleObject* currRect = dynamic_cast<RectangleObject*>(currentobj);
            RectangleObject* iterRect = dynamic_cast<RectangleObject*>((*it));
            if(((currentPos.x+currRect->GetWidth()/2) > (iterPos.x - iterRect->GetWidth()/2) && (currentPos.x-currRect->GetWidth()/2) < (iterPos.x - iterRect->GetWidth()/2))
            && ((currentPos.y+currRect->GetHeight()/2) > (iterPos.y - iterRect->GetHeight()/2) && (currentPos.y-currRect->GetHeight()/2) < (iterPos.y - iterRect->GetHeight()/2)) )
            {
                std::cout << "x y collision with other object" << std::endl;
                return true;
            }
        }

        //std::cout << "different obj" << std::endl;
    }
    std::cout << "no collision" << std::endl;
    return false;
}

bool CollisionDetection::BoundaryCollision(BaseObject* object)
{
    glm::vec3 pos = object->GetPosition();
    glm::vec3 vel = object->GetVelocity();
    glm::vec3 acc = object->GetAcceleration();

    switch (object->GetType())
    {
    case Rect:
        {
            //std::cout << "CalculateBoundCollisionType is rect" << std::endl;
            //RectangleObject* rect = (RectangleObject*)object;
            RectangleObject* rect = dynamic_cast<RectangleObject*>(object);
            if((pos.x + rect->GetWidth()/2) > m_Bounds.OuterX || (pos.x - rect->GetWidth()/2) < m_Bounds.InnerX)
            {
                

                std::cout << "hitting x boundary" << std::endl;
                vel.x = -vel.x;
                object->SetObjectPosVelAcc(pos, vel, acc);
                return true;
            }
            else if((pos.y + rect->GetHeight()/2) > m_Bounds.OuterY || (pos.y - rect->GetHeight()/2) < m_Bounds.InnerY)
            {
                std::cout << "hitting y boundary" << std::endl;
                vel.y = -vel.y;
                object->SetObjectPosVelAcc(pos, vel, acc);
                return true;
            }
            else
            {
                return false;
            }    
        }
    default:
        break;
    }

    return false;
}
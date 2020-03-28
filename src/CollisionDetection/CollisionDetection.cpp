#include "CollisionDetection.h"

CollisionDetection* CollisionDetection::m_Instance = 0; 

CollisionDetection::CollisionDetection()
{
    SetBounds(0, 0, 0, 0);
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

//Return the object it is currently colliding with
CollisionInfo CollisionDetection::InterCollision(std::vector<BaseObject*>  objects, BaseObject* currentobj)
{
    CollisionInfo collisionStruct; 
    unsigned int smallestWidth = 0;

    for(std::vector<BaseObject*>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        //Same object
        if(*it == currentobj)
            continue;

        glm::vec3 currentPos = currentobj->GetPosition();
        glm::vec3 iterPos = (*it)->GetPosition();

        //assumption that currentObj is rect too
        if(currentobj->GetType() == Rect && (*it)->GetType() == Rect)
        {
            RectangleObject* currRect = dynamic_cast<RectangleObject*>(currentobj);
            RectangleObject* iterRect = dynamic_cast<RectangleObject*>((*it));
            if( ((currentPos.x-currRect->GetWidth()/2)  < (iterPos.x + iterRect->GetWidth()/2)  && (currentPos.x + currRect->GetWidth()/2) > (iterPos.x - iterRect->GetWidth()/2))
            &&  ((currentPos.y-currRect->GetHeight()/2) < (iterPos.y + iterRect->GetHeight()/2) && (currentPos.y + currRect->GetHeight()/2) > (iterPos.y - iterRect->GetHeight()/2)) )
            {
                //std::cout << "x y collision with other object" << std::endl;
                //collidingObject = (*it);
                collisionStruct.currentObjectSide = RectGeneral;
                collisionStruct.collisionObject = (*it);
                
                //Extra checks to see which side of the current Rectangle is hit
                if(currRect->GetWidth()/2 < iterRect->GetWidth()/2)
                    smallestWidth = currRect->GetWidth();
                else
                    smallestWidth = iterRect->GetWidth();

                if((currentPos.x + currRect->GetWidth()/2) - (iterPos.x - iterRect->GetWidth()/2) < (smallestWidth/2)/2
                && (currentPos.x + currRect->GetWidth()/2) - (iterPos.x - iterRect->GetWidth()/2) > 0) //Collision on the current obj right side
                {
                    collisionStruct.currentObjectSide = RectRight;
                    std::cout << "Collision on curr objects right side" << std::endl;
                }
                else if((iterPos.x + iterRect->GetWidth()/2) - (currentPos.x - currRect->GetWidth()/2) < (smallestWidth/2)/2
                     && (iterPos.x + iterRect->GetWidth()/2) - (currentPos.x - currRect->GetWidth()/2) > 0) //Collision on the current obj left side
                {
                    collisionStruct.currentObjectSide = RectLeft;
                    std::cout << "Collision on curr objects left side" << std::endl;
                }
                else if(-(iterPos.y - iterRect->GetHeight()/2) + (currentPos.y + currRect->GetHeight()/2) < (smallestWidth/2)/2
                     && -(iterPos.y - iterRect->GetHeight()/2) + (currentPos.y + currRect->GetHeight()/2) > 0) // Collision on the current obj top side
                {
                    collisionStruct.currentObjectSide = RectTop;
                    std::cout << "Collision on top" << std::endl;
                }
                else if((iterPos.y + iterRect->GetHeight()/2) - (currentPos.y - currRect->GetHeight()/2) < (smallestWidth/2)/2 
                     && (iterPos.y + iterRect->GetHeight()/2) - (currentPos.y - currRect->GetHeight()/2) > 0) // Collision on the current obj top side
                {
                    collisionStruct.currentObjectSide = RectBot;
                    std::cout << "Collision on bottom" << std::endl;   
                }
                
            }
        }
    }
    //std::cout << "no collision" << std::endl;
    return collisionStruct;
}

TypeCollision CollisionDetection::BoundaryCollision(BaseObject* object)
{
    glm::vec3 pos = object->GetPosition();
    glm::vec3 vel = object->GetVelocity();
    glm::vec3 acc = object->GetAcceleration();

    switch (object->GetType())
    {
    case Rect:
        {
            RectangleObject* rect = dynamic_cast<RectangleObject*>(object);
            if((pos.x + rect->GetWidth()/2) > m_Bounds.maxX || (pos.x - rect->GetWidth()/2) < m_Bounds.minX)
            {
                //std::cout << "hitting x boundary" << std::endl;
                return TypeCollision::xBoundry;
            }
            else if((pos.y + rect->GetHeight()/2) > m_Bounds.maxY || (pos.y - rect->GetHeight()/2) < m_Bounds.minY)
            {
                //std::cout << "hitting y boundary" << std::endl;
                return TypeCollision::yBoundry;
            }
            else
            {
                return TypeCollision::NoCollision;
            }    
        }
    default:
        break;
    }

    return TypeCollision::NoCollision;
}

bool CollisionDetection::CursorObjectCollision(BaseObject* object, glm::dvec2 cursor)
{
    bool isColliding = false;

    //Flip cursor y coords
    double cursY = cursor.y;
    double cursX = cursor.x; 

    glm::vec3 objPos = object->GetPosition();
    //std::cout << "objPos  x: " << objPos.x << std::endl << "        y: " << objPos.y << std::endl; 
    switch(object->GetType())
    {
        case ObjectType::Rect:
        {
            RectangleObject* rectObj = dynamic_cast<RectangleObject*>(object);
            //std::cout << "Rect" << std::endl;
            if( (cursX < (objPos.x+rectObj->GetWidth()/2)  && cursX > (objPos.x-rectObj->GetWidth()/2))
            &&  (cursY < (objPos.y+rectObj->GetHeight()/2) && cursY > (objPos.y-rectObj->GetHeight()/2)) )
            {
                //std::cout << "cursor collision with obj" << std::endl;
                isColliding = true;
            }
            break;
        }
        default:
            break;
    }

    return isColliding;
}
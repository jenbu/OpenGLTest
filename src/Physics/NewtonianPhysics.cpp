#include "NewtonianPhysics.h"

NewtonianPhysics* NewtonianPhysics::m_Instance = 0; 
const float g = 9.81;

NewtonianPhysics::NewtonianPhysics()
: m_CurrentVel{ 0.0f, 0.0f}, m_DeltaT(0.0), m_ToggleCollision(false)
{

}

NewtonianPhysics::~NewtonianPhysics()
{

}

NewtonianPhysics* NewtonianPhysics::GetInstance()
{
    if(!m_Instance)
    {
        m_Instance = new NewtonianPhysics;
    }
    return m_Instance;
}

//Checks boundary collision and updates velocity and position
void NewtonianPhysics::UpdateVelPos(glm::vec3 acc)
{
    glm::vec3 vel = m_CurrentObject->GetVelocity();
    glm::vec3 pos = m_CurrentObject->GetPosition();

    if(BoundCollision(m_CurrentObject) /*&& m_ToggleCollision == false*/)
    {
        //velvec is updated in CalculateBoundCollision()
        vel = m_CurrentObject->GetVelocity();
    }
    else
    {
        vel.x += acc.x*m_DeltaT;
        vel.y += acc.y*m_DeltaT; 
    }

    pos.x += vel.x*m_DeltaT;
    pos.y += vel.y*m_DeltaT;

    m_CurrentObject->SetObjectPosVelAcc(pos, vel, acc);
}

void NewtonianPhysics::Calculate(std::vector<BaseObject*> objects)
{
    glm::vec3 acc, vel;

    float air_res;

    for(int i = 0; i < objects.size(); i++)
    {
        m_CurrentObject = objects[i];
        acc = m_CurrentObject->GetAcceleration();
        vel = m_CurrentObject->GetVelocity();

        //Calculate acceleration
        if(vel.y > 0)
            air_res = - pow(vel.y, 2)/2;
        else
            air_res = pow(vel.y, 2)/2;
            
        acc.y = -g*2 + air_res/m_CurrentObject->GetMass();

        //Update
        UpdateVelPos(acc);

    }
}

bool NewtonianPhysics::BoundCollision(BaseObject* object)
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

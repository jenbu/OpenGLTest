#include "NewtonianPhysics.h"

NewtonianPhysics* NewtonianPhysics::m_Instance = 0; 
const float g = 9.81;

NewtonianPhysics::NewtonianPhysics()
: m_CurrentVel{ 0.0f, 0.0f}, m_DeltaT(0.0), m_ToggleCollision(false), m_PhysicsEnabled(false)
{
    m_CollisionDetector = CollisionDetection::GetInstance();
    m_CollisionDetector->SetBounds(0, ResolutionWidth, 0 ,ResolutionHeight);

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

//updates velocity and position
void NewtonianPhysics::UpdateVelPos(glm::vec3 acc)
{
    glm::vec3 vel = m_CurrentObject->GetVelocity();
    glm::vec3 pos = m_CurrentObject->GetPosition();


    vel.x += acc.x*m_DeltaT;
    vel.y += acc.y*m_DeltaT; 

    pos.x += vel.x*m_DeltaT;
    pos.y += vel.y*m_DeltaT;

    m_CurrentObject->SetObjectPosVelAcc(pos, vel, acc);
}

/*void NewtonianPhysics::UpdateVelPosTest()
{
    glm::vec3 vel = m_CurrentObject->GetVelocity();
    glm::vec3 pos = m_CurrentObject->GetPosition();


    vel.x += acc.x*m_DeltaT;
    vel.y += acc.y*m_DeltaT; 

    pos.x += vel.x*m_DeltaT;
    pos.y += vel.y*m_DeltaT;

    m_CurrentObject->SetObjectPosVelAcc(pos, vel, acc);
}*/

//Really want to do this way?
void NewtonianPhysics::CalculateMomentum(BaseObject* obj1, BaseObject* obj2)
{
    unsigned int massOne, massTwo;
    glm::vec3 velOne, velTwo;
    massOne = obj1->GetMass();
    massTwo = obj2->GetMass();
    velOne = obj1->GetVelocity();
    velTwo = obj2->GetVelocity();
}

void GetSpringDampForces()
{

}


glm::vec3 NewtonianPhysics::CollisionForce(BaseObject* currObj, CollisionInfo collInfo)
{
    BaseObject* collObj = collInfo.collisionObject;
    glm::vec3 velCurr, posCurr, posColl, velColl;
    velCurr = currObj->GetVelocity(); velColl = collObj->GetVelocity();
    posCurr = currObj->GetPosition(); posColl = collObj->GetPosition();

    glm::vec3 F_k(0.0f, 0.0f, 0.0f);
    
    //Calculate equivalent spring force
    float F_ke = (currObj->GetSpringConst() * collObj->GetSpringConst())/(currObj->GetSpringConst() + collObj->GetSpringConst());

    //Assume rectangle
    RectangleObject* currRect = dynamic_cast<RectangleObject*>(currObj);
    RectangleObject* collRect = dynamic_cast<RectangleObject*>(collObj);
    //std::cout << "CollisionType: " << collInfo.currentObjectSide << std::endl;
    switch (collInfo.currentObjectSide)
    {
    case RectLeft:
        F_k.x = ((posColl.x + collRect->GetWidth()/2) - (posCurr.x - currRect->GetWidth()/2))*F_ke;
        //if((posColl.y - posCurr.y) > 0)


        break;
    case RectRight:
        F_k.x = -((posCurr.x + currRect->GetWidth()/2) - (posColl.x - collRect->GetWidth()/2))*F_ke;
        break;
    case RectTop:
        F_k.y = -((posCurr.y + currRect->GetHeight()/2) - (posColl.y - collRect->GetHeight()/2))*F_ke;
        break;
    case RectBot:
        F_k.y = -((posCurr.y - currRect->GetHeight()/2) - (posColl.y + collRect->GetHeight()/2))*F_ke;
        break;
    default:

        break;
    }

    return F_k;
}

float NewtonianPhysics::BoundaryForces(TypeCollision coll)
{
    glm::vec3 vel = m_CurrentObject->GetVelocity();
    glm::vec3 pos = m_CurrentObject->GetPosition();
    float F_kb = 0.0f;

    //Assume rectangle for now
    RectangleObject* currRect = dynamic_cast<RectangleObject*>(m_CurrentObject);

    switch (coll)
    {
    case TypeCollision::xBoundry:
        {
            vel = glm::vec3(-vel.x, vel.y, vel.z);
            m_CurrentObject->SetObjectPosVelAcc(m_CurrentObject->GetPosition(), vel, m_CurrentObject->GetAcceleration());
            break;
        }
    case TypeCollision::yBoundry:

        if((pos.y + currRect->GetHeight()/2) < ResolutionHeight)
            F_kb = -(pos.y-currRect->GetHeight()/2)*m_Boundaryk + (-vel.y)*m_Boundaryb; 
        break;
        
    default:
        break;
    }

    return F_kb;
}

float NewtonianPhysics::CursorForces(BaseObject* currObj)
{
    //Flip cursor coord
    double cursY = MouseEventHandler::GetInstance()->GetCursorPos().y;
    double cursX = MouseEventHandler::GetInstance()->GetCursorPos().x;

    switch(currObj->GetType())
    {
        case ObjectType::Rect:
        {
            RectangleObject* rectObj = dynamic_cast<RectangleObject*>(currObj);

            break;
        }
    }

    return 5000.0f;


}

void NewtonianPhysics::Calculate(std::vector<BaseObject*> objects)
{

    glm::vec3 acc, vel;

    float air_res, F_Boundaryk, F_curs = 0;
    glm::vec3 F_Collision;

    TypeCollision boundaryCollitionType;
    CollisionInfo collidingObject;

    for(int i = 0; i < objects.size(); i++)
    {
        F_Collision = glm::vec3(0, 0, 0);
        m_CurrentObject = objects[i];
        acc = m_CurrentObject->GetAcceleration();
        vel = m_CurrentObject->GetVelocity();

        //Collition between objects and forces
        collidingObject = m_CollisionDetector->InterCollision(objects, m_CurrentObject);
        if(collidingObject.collisionObject != NULL)
        {
            F_Collision = CollisionForce(m_CurrentObject, collidingObject);
        }

        //Boundary Collision and forces
        if(boundaryCollitionType = m_CollisionDetector->BoundaryCollision(m_CurrentObject))
        {
            F_Boundaryk = BoundaryForces(boundaryCollitionType);
            //std::cout << "boundary force: " << F_Boundaryk << std::endl;
        }
        else
        {
            F_Boundaryk = 0.0f;
        }
        
        //Cursor collision
        //if(m_CollisionDetector->CursorObjectCollision(m_CurrentObject, MouseEventHandler::GetInstance()->GetCursorPos()))
        //{
        //    F_curs = CursorForces(m_CurrentObject);
        //    std::cout << "Cursor collision with obj" << std::endl;
        //}
        //else
            F_curs = 0.0f;
        

        //Calculate acceleration and update
        if(m_PhysicsEnabled)
        {
            if(m_CurrentObject->IsPhysEnabled())
            {
                //Calculate acceleration
                if(vel.y > 0)
                    air_res = - pow(vel.y, 2)/2;
                else
                    air_res = pow(vel.y, 2)/2;
                    
                acc.x = F_Collision.x/m_CurrentObject->GetMass();
                acc.y = -g*2 + (F_Boundaryk + F_Collision.y + F_curs)/m_CurrentObject->GetMass() ;// + air_res/m_CurrentObject->GetMass();

                //Update
                UpdateVelPos(acc);
            }
        }
    }

    
}


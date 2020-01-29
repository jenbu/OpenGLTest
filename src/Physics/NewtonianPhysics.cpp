#include "NewtonianPhysics.h"

NewtonianPhysics* NewtonianPhysics::m_Instance = 0; 
const float g = 9.81;

NewtonianPhysics::NewtonianPhysics()
: m_CurrentVel{ 3.0f, 2.0f}
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

void NewtonianPhysics::Calculate(std::vector<BaseObject*> objects)
{
    
    for(int i = 0; i < objects.size(); i++)
    {
        //std::cout << "Object name: "<< objects[i]->GetName() << " Object Weight: "<< objects[i]->GetMass() << std::endl;
        m_CurrentObjPosVelAcc = objects[i]->GetObjectPosVelAcc();
        //To do, fix everything moving together problem, make resolution global!
        if((m_CurrentObjPosVelAcc.PosVec.x + m_CurrentVel[0]) > 1280 || (m_CurrentObjPosVelAcc.PosVec.x + m_CurrentVel[0]) < 0 ) 
            m_CurrentVel[0] = -m_CurrentVel[0];

        if((m_CurrentObjPosVelAcc.PosVec.y + m_CurrentVel[1]) > 720 || (m_CurrentObjPosVelAcc.PosVec.y + m_CurrentVel[1]) < 0 ) 
            m_CurrentVel[1] = -m_CurrentVel[1];
        
        m_CurrentObjPosVelAcc.PosVec = glm::vec3(m_CurrentObjPosVelAcc.PosVec.x + m_CurrentVel[0], 
                                                 m_CurrentObjPosVelAcc.PosVec.y + m_CurrentVel[1], 0);
        objects[i]->SetObjectPosVelAcc(m_CurrentObjPosVelAcc);
    }
}
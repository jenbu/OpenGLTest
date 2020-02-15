#include "BaseObject.h"

unsigned int BaseObject::m_ObjectCount = 0;

BaseObject::BaseObject(glm::vec3 pos, glm::vec3 vel, float rot = 0.0f, float mass = 100)
 : m_Name("Base"), m_Mass(mass), m_PosVelAcc({glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), 0}), m_Spring(100000)
    
{
    ++m_ObjectCount;

    m_PosVec = pos;
    m_VelVec = vel;
    m_AccVec = glm::vec3(0, 0, 0);

    m_PosVelAcc.PosVec = pos;
    m_PosVelAcc.VelVec = vel;
    m_PosVelAcc.AccVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.rot = 1231;


    m_Color = {1.0f, 0.0f, 0.5f, 1.0f};
}

BaseObject::~BaseObject()
{

}


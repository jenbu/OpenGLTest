#include "BaseObject.h"

unsigned int BaseObject::m_ObjectCount = 0;

BaseObject::BaseObject(int posX = 0, int posY = 0, float rot = 0.0f, float mass = 100)
 : m_Name("Base"), m_Mass(mass), m_PosVelAcc({glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), 0})
    
{
    ++m_ObjectCount;

    m_PosVec = glm::vec3(posX, posY, 0);
    m_VelVec = glm::vec3(-31.0f, 0, 0);
    m_AccVec = glm::vec3(0, 0, 0);

    m_PosVelAcc.PosVec = glm::vec3(posX, posY, 0);
    m_PosVelAcc.VelVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.AccVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.rot = 1231;


    m_Color = {1.0f, 0.0f, 0.5f, 1.0f};
}

BaseObject::~BaseObject()
{

}


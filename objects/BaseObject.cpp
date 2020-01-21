#include "BaseObject.h"

std::vector<float> BaseObject::m_VertexCoords{};
std::vector<unsigned int> BaseObject::m_Indices{};
std::vector<unsigned int> BaseObject::m_IndexOffsets{};
unsigned int BaseObject::m_ObjectCount = 0;

BaseObject::BaseObject(int posX = 0, int posY = 0, float rot = 0.0f, float mass = 100)
 : m_Name("Base"), m_Mass(mass), m_PosVelAcc({glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), 0})
    
{
    ++m_ObjectCount;
    std::cout << "BaseObject constructor: x and y: " << posX << ", " << posY << std::endl;
    m_PosVelAcc.PosVec = glm::vec3(posX, posY, 0);
    m_PosVelAcc.VelVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.VelVec = glm::vec3(0, 0, 0);
    m_PosVelAcc.rot = 0;
    //m_PosVelAcc = { glm::vec3(posX, posY, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), rot };
    std::cout << "BaseObject constructor: m_PosVelAcc x:" << m_PosVelAcc.PosVec.x << std::endl;
    m_Color = {1.0f, 0.0f, 0.5f, 1.0f};
}

BaseObject::~BaseObject()
{

}

void BaseObject::SetObjectPosVel(glm::vec3 acc, float deltaTime)
{
    
}
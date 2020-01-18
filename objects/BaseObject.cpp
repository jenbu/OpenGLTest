#include "BaseObject.h"

std::vector<float> BaseObject::m_VertexCoords{};
std::vector<unsigned int> BaseObject::m_Indices{};
std::vector<ObjectTransformation> BaseObject::m_ObjectTrans{};
std::vector<unsigned int> BaseObject::m_IndexOffsets{};
unsigned int BaseObject::m_ObjectCount = 0;

BaseObject::BaseObject(int posX = 0, int posY = 0, float rot = 0.0f, float mass = 100)
 : m_Name("Base"), m_Mass(mass)
    
{
    ++m_ObjectCount;
    m_ObjectTrans.push_back({ glm::vec3(posX, posY, 0), rot });
    std::cout << "pushing back x: " << posX << " y: " << posY << std::endl;
    m_Color = {1.0f, 0.0f, 0.5f, 1.0f};
}

BaseObject::~BaseObject()
{

}
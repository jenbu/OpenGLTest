#include "RectangleObject.h"

unsigned int RectangleObject::m_RectCount = 0;

RectangleObject::RectangleObject(glm::vec3 pos, glm::vec3 vel, std::vector<EBMath::Vertex2D> vertices, float rot = 0, unsigned int width = 100, 
                                 unsigned int height = 100, float mass = 100)
: m_Width(width), m_Height(height), BaseObject(pos, vel, vertices, rot, mass), m_NumIndexes(6)
{
    ++m_RectCount;
    std::string rectName("Rectangle ");
    rectName.append(std::to_string(m_RectCount));
    this->SetName(rectName);



}

RectangleObject::~RectangleObject()
{

}

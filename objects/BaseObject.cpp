#include "BaseObject.h"


BaseObject::BaseObject(std::string name, float posX, float posY)
 : m_Rotation(0.0f), m_Translation(posX, posY, 0), m_Color{ 1.0f, 0.0f, 0.5f, 1.0f }, m_Name(name)
    
{

}

BaseObject::~BaseObject()
{

}
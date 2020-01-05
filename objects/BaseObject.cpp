#include "BaseObject.h"


BaseObject::BaseObject(float posX, float posY)
 : m_Rotation(0.0f), m_Translation(posX, posY, 0), m_Name("Base")
    
{
    m_Color.push_back(1.0f); m_Color.push_back(0.0f);
    m_Color.push_back(0.5f); m_Color.push_back(1.0f);
}

BaseObject::~BaseObject()
{

}
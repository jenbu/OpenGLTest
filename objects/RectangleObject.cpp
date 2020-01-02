#include "RectangleObject.h"

RectangleObject::RectangleObject(float x, float y)
: m_Width(100), m_Height(100), BaseObject(x, y)
{
    ++m_RectCount;
    std::string rectName("Rectangle ");
    rectName.append(std::to_string(m_RectCount));
    this->SetName(rectName);    

}

RectangleObject::~RectangleObject()
{

}

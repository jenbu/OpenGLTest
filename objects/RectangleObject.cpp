#include "RectangleObject.h"

RectangleObject::RectangleObject(std::string name, float x, float y)
: m_Width(100), m_Height(100), BaseObject(name, x, y)
{
    ++m_RectCount;
}

RectangleObject::~RectangleObject()
{

}

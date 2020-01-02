#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "BaseObject.h"
#include <iostream>


class RectangleObject : public BaseObject
{
private:
    int m_Width;
    int m_Height;
    static int m_RectCount;

public:
    RectangleObject(float x, float y);
    ~RectangleObject();

    inline int GetRectCount() { return m_RectCount; };

};

#endif
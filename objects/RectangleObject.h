#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "BaseObject.h"
#include <iostream>


class RectangleObject : public BaseObject
{
private:
    static unsigned int m_RectCount;
    unsigned int m_Width, m_Height;

    void addRectData(float width, float height);

public:
    RectangleObject(float x, float y, float rot, unsigned int width, unsigned int height, float mass);
    ~RectangleObject();

    inline int GetRectCount() { return m_RectCount; };
    void DrawObject() override;

};

#endif
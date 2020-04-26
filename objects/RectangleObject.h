#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "BaseObject.h"
#include <iostream>


class RectangleObject : public BaseObject
{
public:
    RectangleObject(glm::vec3 pos, glm::vec3 vel, VertexIndexData vertexindexdata, 
                    float rot, unsigned int width, unsigned int height, float mass);
    ~RectangleObject();

    inline int GetRectCount() { return m_RectCount; };  
    ObjectType GetType() override { return Rect; }
    unsigned int GetNumIndices() override { return m_NumIndexes; }

    glm::vec3 GetGeometry() override { return glm::vec3(m_Width, m_Width, 0); }
    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }

private:
    static unsigned int m_RectCount;
    unsigned int m_Width, m_Height;
    unsigned int m_NumIndexes; //Number of indeces for rectangle

};

#endif
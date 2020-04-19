#pragma once

#include "BaseObject.h"

#include "glm/glm.hpp"
#include "EBMath.h"

class CircleObject : public BaseObject 
{
public:
    CircleObject(float radius, glm::vec3 pos, glm::vec3 vel, 
                 VertexIndexData vertexindexdata, float rot, float mass);
    ~CircleObject();


private:
    float m_Radius;


};
#include "CircleObject.h"


CircleObject::CircleObject(float radius, glm::vec3 pos, glm::vec3 vel, VertexIndexData vertexindexdata,
                           float rot = 0, float mass = 10)
: BaseObject(pos, vel, vertexindexdata, rot, mass)
{

}

CircleObject::~CircleObject()
{
    
}

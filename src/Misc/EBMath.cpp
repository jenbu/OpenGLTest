#include "EBMath.h"

namespace EBMath
{
    float AbsoluteVelocity(glm::vec3 vel)
    {
        return sqrt(pow(vel.x, 2) + pow(vel.y, 2) + pow(vel.z, 2));
    }   
}
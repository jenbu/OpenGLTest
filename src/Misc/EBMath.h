#ifndef EBMATH_H
#define EBMATH_H

#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace EBMath 
{
    enum Direction
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };


    float AbsoluteVelocity(glm::vec3 vel);

    Direction VectorDirection(glm::vec2 vec);

    struct Vertex2D
    {
        float x;
        float y;
    };
}



#endif
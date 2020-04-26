#ifndef EBMATH_H
#define EBMATH_H

#include <math.h>
#include <vector>
#include <iostream>

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

    struct Vertex2D
    {
        float x;
        float y;
    };

    float AbsoluteVelocity(glm::vec3 vel);

    Direction VectorDirection(glm::vec2 vec);

    std::vector<float> ConvertVertex2DVecToFloatVec(std::vector<EBMath::Vertex2D> vec);
    std::vector<EBMath::Vertex2D> ConvertFloatVecToVertex2D(std::vector<float> vec);

}



#endif
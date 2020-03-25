#include "EBMath.h"

namespace EBMath
{
    float AbsoluteVelocity(glm::vec3 vel)
    {
        return sqrt(pow(vel.x, 2) + pow(vel.y, 2) + pow(vel.z, 2));
    }


    Direction VectorDirection(glm::vec2 vec)
    {
        glm::vec2 compass[]
        {
            glm::vec2(0.0f, 1.0f), //up
            glm::vec2(1.0f, 0.0f), //right
            glm::vec2(0.0f, -1.0f),//down
            glm::vec2(-1.0f, 0.0f) //left
        };

        float max = 0.0f;
        int bestMatch = -1;
        for(int i = 0; i < 4; i++)
        {
            float dotProduct = glm::dot(glm::normalize(vec), compass[i]);
            if(dotProduct > max)
            {
                max = dotProduct;
                bestMatch = i;
            }
        }

        return (Direction)bestMatch;
    }   
}
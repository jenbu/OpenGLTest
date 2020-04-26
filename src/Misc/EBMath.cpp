#include "EBMath.h"

namespace EBMath
{
    float AbsoluteVelocity(glm::vec3 vel)
    {
        return sqrt(pow(vel.x, 2) + pow(vel.y, 2) + pow(vel.z, 2));
    }


    std::vector<float> ConvertVertex2DVecToFloatVec(std::vector<EBMath::Vertex2D> vec)
    {
        std::vector<float> tempVec;

        for(int i = 0; i < vec.size(); i++)
        {
            tempVec.push_back(vec[i].x);
            tempVec.push_back(vec[i].y);
        }

        return tempVec;
    }

    std::vector<EBMath::Vertex2D> ConvertFloatVecToVertex2D(std::vector<float> vec)
    {
        std::vector<EBMath::Vertex2D> tempVec;
        if(vec.size() % 2 != 0)
        {
            return tempVec;
        }

        int counter = 0;
        for(int i = 0; i < vec.size(); i++)
        {
            counter++;
            if(counter == 2)
            {
                counter = 0;

                tempVec.push_back({vec[i], vec[i-1]});
            }
        }
        return tempVec;
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
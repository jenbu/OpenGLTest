#include "SATCollisionDetection.h"

SATCollisionDetection::SATCollisionDetection()
{

}

SATCollisionDetection::~SATCollisionDetection()
{

}

bool SATCollisionDetection::CollisionDetection(std::vector<BaseObject*> objects)
{

    for(int i = 0; i < objects.size(); i++)
    {
        std::cout << objects[i]->GetName() << std::endl;
    }

}
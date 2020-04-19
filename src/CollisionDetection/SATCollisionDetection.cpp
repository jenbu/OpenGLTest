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
        std::vector<EBMath::Vertex2D> vertices = objects[i]->GetVerticesPos(); 
        for(int k = 0; k < vertices.size(); k++)
        {
            std::cout << "(" << vertices[i].x << ", " << vertices[i].y << ")" << std::endl;
        }
    }

}
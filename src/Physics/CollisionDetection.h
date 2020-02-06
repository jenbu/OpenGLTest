#pragma once
#include "BaseObject.h"
#include "RectangleObject.h"
#include <vector>

class CollisionDetection
{
public:
    static CollisionDetection* GetInstance();
    bool InterCollision(std::vector<BaseObject*>  objects, BaseObject* currentobj);
    bool BoundaryCollision(BaseObject* object);

private:
    CollisionDetection();
    ~CollisionDetection();


    static CollisionDetection* m_Instance;
};
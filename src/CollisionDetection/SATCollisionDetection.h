#pragma once

#include <vector>

#include "BaseObject.h"




class SATCollisionDetection
{
public:
    SATCollisionDetection();
    ~SATCollisionDetection();

    bool CollisionDetection(std::vector<BaseObject*> objects);

private:


};
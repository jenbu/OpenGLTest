#pragma once

#include <vector>

#include "BaseObject.h"
#include "MouseEventHandler.h"
#include "CollisionDetection.h"

class MouseManipulator
{
public:
    MouseManipulator();

    void Manipulate(std::vector<BaseObject*> objects);
private:
    MouseEventHandler* m_MouseEvents;
    CollisionDetection* m_Collision;
    std::vector<bool> m_toggleSelection;

};
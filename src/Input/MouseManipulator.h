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
    bool ObjectSelection(BaseObject* obj);
    void Drag();
private:
    MouseEventHandler* m_MouseEvents;

    BaseObject* m_SelectedObj;

    bool m_SelectionToggle;
    bool m_EnableDrag;
    bool m_Dragging;

    CollisionDetection* m_Collision;
    std::vector<bool> m_toggleSelection;

};
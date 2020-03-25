#pragma once

#include "Constants.h"
#include "BaseObject.h"
#include "RectangleObject.h"
#include <vector>

struct WorldBounds
{
    unsigned int minX;
    unsigned int maxX;
    unsigned int minY;
    unsigned int maxY;
};

enum TypeCollision
{
    NoCollision = 0,
    xBoundry = 1,
    yBoundry = 2,
    RectGeneral,
    RectBot,
    RectTop,
    RectRight,
    RectLeft
};

struct CollisionInfo
{
    BaseObject* collisionObject = NULL;
    TypeCollision currentObjectSide = TypeCollision::NoCollision;
};

class CollisionDetection
{
public:
    static CollisionDetection* GetInstance();
    inline void SetBounds(unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy) { m_Bounds = { minx, maxx, miny, maxy }; };
    
    CollisionInfo InterCollision(std::vector<BaseObject*>  objects, BaseObject* currentobj);
    TypeCollision BoundaryCollision(BaseObject* object);
    bool CursorObjectCollision(BaseObject* object, glm::dvec2 cursor);


private:
    CollisionDetection();
    ~CollisionDetection();


    static CollisionDetection* m_Instance;

    WorldBounds m_Bounds;
};
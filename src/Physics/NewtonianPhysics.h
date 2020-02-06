#pragma once

#include <vector>
#include "BaseObject.h"
#include "RectangleObject.h"
#include "CollisionDetection.h"

struct WorldBounds
{
    int OuterX;
    int InnerX;
    int OuterY;
    int InnerY;
    float spring_k = 400;
};

class NewtonianPhysics
{

public:
    static NewtonianPhysics* GetInstance();
    void Calculate(std::vector<BaseObject*> objects);

    inline void setDeltaT(float delta){ m_DeltaT = delta; };
    inline void SetBounds(int outerx, int innerx, int outery, int innery) { m_Bounds = { outerx, innerx, outery, innery }; };

    inline float GetDeltaT() { return m_DeltaT; };

private:
    static NewtonianPhysics* m_Instance;
    NewtonianPhysics();
    ~NewtonianPhysics();

    CollisionDetection* m_CollisionDetector;

    void UpdateVelPos(glm::vec3 acc);

    bool m_ToggleCollision;

    float m_DeltaT;
    WorldBounds m_Bounds;

    ObjectPosVelAcc m_CurrentObjPosVelAcc;
    BaseObject* m_CurrentObject;
    std::vector<float> m_CurrentVel;

};
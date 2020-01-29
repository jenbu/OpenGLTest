#pragma once

#include <vector>
#include "BaseObject.h"

class NewtonianPhysics
{

public:
    static NewtonianPhysics* GetInstance();
    void Calculate(std::vector<BaseObject*> objects);

    inline void setDeltaT(float delta){ m_DeltaT = delta; };
    inline float GetDeltaT() { return m_DeltaT; };

private:
    static NewtonianPhysics* m_Instance;
    NewtonianPhysics();
    ~NewtonianPhysics();

    float m_DeltaT;

    ObjectPosVelAcc m_CurrentObjPosVelAcc;
    std::vector<float> m_CurrentVel;

};
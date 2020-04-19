#pragma once

#include "Constants.h"
#include <vector>
#include "BaseObject.h"
#include "RectangleObject.h"
#include "CollisionDetection.h"
#include "InputEventHandler.h"



class NewtonianPhysics
{

public:
    static NewtonianPhysics* GetInstance();
    void Calculate(std::vector<BaseObject*> objects);

    inline void setDeltaT(double delta){ m_DeltaT = delta; };
    inline float GetDeltaT() { return m_DeltaT; };
    inline bool GetPhysicsEnabled() { return m_PhysicsEnabled; }
    inline void enablePhysics(bool enable) { m_PhysicsEnabled = enable; }

private:
    static NewtonianPhysics* m_Instance;
    NewtonianPhysics();
    ~NewtonianPhysics();


    void UpdateVelPos(glm::vec3 acc);
    void UpdateVelPosTest();
    void CalculateMomentum(BaseObject* obj1, BaseObject* obj2);
    
    
    float BoundaryForces(TypeCollision coll);

    //Calculate tranlation, rotational force on the object
    //params:   currObj, the primary object calculating forces on
    //          collInfo, struct containing information about the object acting forces upon the primary obj
    glm::vec3 CollisionForce(BaseObject* currObj, CollisionInfo collInfo);

    float CursorForces(BaseObject* currObj);

    bool m_PhysicsEnabled;
    bool m_ToggleCollision;
    float const m_Boundaryk = 3000;
    float const m_Boundaryb = 5;

    double m_DeltaT;

    
    CollisionDetection* m_CollisionDetector;
    ObjectPosVelAcc m_CurrentObjPosVelAcc;
    BaseObject* m_CurrentObject;
    std::vector<float> m_CurrentVel;


};
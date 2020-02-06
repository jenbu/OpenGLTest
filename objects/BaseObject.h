
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <vector>

struct ObjectPosVelAcc
{
    glm::vec3 PosVec;
    glm::vec3 VelVec;
    glm::vec3 AccVec;
    float rot = 0;

};

enum ObjectType
{
    Base = 0,
    Rect
};

class BaseObject
{
public:
    BaseObject(glm::vec3 pos, glm::vec3 vel, float rot, float mass);
    ~BaseObject();

    inline void SetName(std::string name) {m_Name = name; };
    inline void SetColors(std::vector<float> colors) { m_Color = colors; };
    void SetObjectPosVelAcc(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc) 
    { m_PosVec = pos; m_VelVec = vel, m_AccVec = acc; }
    
    inline std::vector<float> GetColors() { return m_Color; };
    inline std::string GetName() { return m_Name; }
    virtual ObjectType GetType() {};
    virtual void GetGeometry() {};
    inline float GetMass() { return m_Mass; }
     
    //ObjectPosVelAcc GetObjectPosVelAcc() { return m_PosVelAcc; }
    inline glm::vec3 GetPosition() { return m_PosVec; }
    inline glm::vec3 GetVelocity() { return m_VelVec; }
    inline glm::vec3 GetAcceleration() { return m_AccVec; }
     

    virtual unsigned int GetNumIndices() {}

    template<typename T>
    void AppendObject(T* object)
    {
        m_Objects.push_back(object);
    }

    static std::vector<BaseObject*> m_Objects;
private:   
    
    glm::mat4 m_Proj, m_View, m_model;
    std::vector<float> m_Color;

    std::string m_Name;
    ObjectType m_Type;

    //Positional properties
    ObjectPosVelAcc m_PosVelAcc;

    glm::vec3 m_AccVec;
    glm::vec3 m_VelVec;
    glm::vec3 m_PosVec;

    //Physical properties
    float m_Mass;


    

protected:
    //static std::vector<float> m_VertexCoords;
    //static std::vector<unsigned int> m_Indices;
    //static std::vector<unsigned int> m_IndexOffsets;
    static unsigned int m_ObjectCount;


    

};

#endif

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

struct ObjectData
{
    std::vector<float> VertexPosition;
    std::vector<unsigned int> VertexIndices;
    std::vector<unsigned int> ObjectIndexOffset;
};


class BaseObject
{
public:
    BaseObject(int posX, int posY, float rot, float mass);
    ~BaseObject();

    inline void SetName(std::string name) {m_Name = name; };
    inline void SetColors(std::vector<float> colors) { m_Color = colors; };
    
    inline std::vector<float> GetColors() { return m_Color; };
    inline std::string GetName() { return m_Name; }
    //inline std::vector<BaseObject*> GetObjects() { return m_Objects; } 
    ObjectPosVelAcc GetObjectPosVelAcc() { return m_PosVelAcc; } 
    void SetObjectPosVelAcc(ObjectPosVelAcc data) { m_PosVelAcc = data; };
    inline float GetMass() { return m_Mass; }

    virtual unsigned int GetNumIndices() {}

    template<typename T>
    void AppendObject(T* object)
    {
        m_Objects.push_back(object);
    }

    virtual void DrawObject() {};
    static std::vector<BaseObject*> m_Objects;
private:   
    
    glm::mat4 m_Proj, m_View, m_model;
    std::vector<float> m_Color;

    std::string m_Name;
    ObjectPosVelAcc m_PosVelAcc;

    //Physical properties
    float m_Mass;
    glm::vec3 m_Acceleration;
    glm::vec3 m_Velocity;
    

protected:
    //static std::vector<float> m_VertexCoords;
    //static std::vector<unsigned int> m_Indices;
    //static std::vector<unsigned int> m_IndexOffsets;
    static unsigned int m_ObjectCount;


    

};

#endif
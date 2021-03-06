
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <iostream>
#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "EBMath.h"

struct VertexIndexData
{
    std::vector<EBMath::Vertex2D> vertex2DVec;
    std::vector<unsigned int> indices;
    unsigned int IndexOffset;
};

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
    BaseObject(glm::vec3 pos, glm::vec3 vel, VertexIndexData vertexindexdata, 
               float rot, float mass);
    ~BaseObject();

    inline void ToggleObjPhysics() { m_ObjPhysEnabled = !m_ObjPhysEnabled; }
    inline bool IsPhysEnabled() { return m_ObjPhysEnabled; }
    void TransformVertices(glm::mat4 mvp);

    //Setters
    inline void SetName(std::string name) {m_Name = name; };
    inline void SetColors(std::vector<float> colors) { m_Color = colors; };
    inline void SetObjectPos(glm::vec3 pos) { m_PosVec = pos; }
    inline void SetObjectPosVelAcc(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc) 
    { m_PosVec = pos; m_VelVec = vel, m_AccVec = acc; }
    
    //Getters
    inline std::vector<float>     GetColors() { return m_Color; };
    inline std::string            GetName() { return m_Name; }
    virtual ObjectType            GetType() {};
    virtual glm::vec3             GetGeometry() {};
    inline float                  GetMass() { return m_Mass; }
    inline unsigned int           GetSpringConst() { return m_Spring; }
    std::vector<EBMath::Vertex2D> GetVerticesPos() { return m_VertexPosition; }
    std::vector<float>            GetBaseVertices() { return m_BaseVertices; } //vertices passed to vertexbuf
    std::vector<unsigned int>     GetBaseIndices() { return m_Indices; }
    unsigned int                  GetIndicesOffset() { return m_IndexOffset; }
    unsigned int                  GetIndicesSize() { return m_Indices.size(); }
     
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
    
    std::string m_Name;
    ObjectType m_Type;
    unsigned int m_Spring;
    
    //Geometric propertier
    std::vector<EBMath::Vertex2D> m_VertexPosition;

    //OpenGL and transformation
    std::vector<unsigned int> m_Indices;
    unsigned int m_IndexOffset;
    std::vector<float> m_BaseVertices;
    glm::mat4 m_Proj, m_View, m_model;
    std::vector<float> m_Color;



    //Positional properties
    ObjectPosVelAcc m_PosVelAcc;
    glm::vec3 m_AccVec;
    glm::vec3 m_VelVec;
    glm::vec3 m_PosVec;

    //Physical properties
    float m_Mass;
    bool m_ObjPhysEnabled;


    

protected:
    //static std::vector<float> m_VertexCoords;
    //static std::vector<unsigned int> m_Indices;
    //static std::vector<unsigned int> m_IndexOffsets;
    static unsigned int m_ObjectCount;


    

};

#endif
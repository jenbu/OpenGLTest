
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <vector>

struct ObjectTransformation
{
    glm::vec3 vec;
    float rot = 0;

};

struct ObjectData
{
    std::vector<float> position;
    std::vector<unsigned int> indices;
    std::vector<ObjectTransformation> trans;
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
    inline std::vector<BaseObject*> GetObjects() { return m_Objects; } 
    ObjectData GetObjectData() { return { m_VertexCoords, m_Indices, m_ObjectTrans, m_IndexOffsets }; }

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

    //Physical properties
    float m_Mass;

protected:
    static std::vector<float> m_VertexCoords;
    static std::vector<unsigned int> m_Indices;
    static std::vector<unsigned int> m_IndexOffsets;
    static std::vector<ObjectTransformation> m_ObjectTrans;
    static unsigned int m_ObjectCount;


    

};

#endif

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <vector>


class BaseObject
{

private:   
    
    glm::mat4 m_Proj, m_View, m_model;
    glm::vec3 m_Translation;
    float m_Rotation;
    std::vector<float> m_Color;

    std::string m_Name;

public:
    BaseObject(float posX, float posY);
    ~BaseObject();

    inline void SetTranslation(glm::vec3 translation) { m_Translation = translation; };
    inline void SetName(std::string name) {m_Name = name; };
    inline void SetColors(std::vector<float> colors) { m_Color = colors; };
    inline void SetRotation(float rot) { m_Rotation = rot; };
    
    inline glm::vec3* GetTranslation() { return &m_Translation; };
    inline std::vector<float> GetColors() { return m_Color; };
    inline std::string GetName() { return m_Name; };
    inline float* GetRotationPtr() { return &m_Rotation; };
    


};

#endif
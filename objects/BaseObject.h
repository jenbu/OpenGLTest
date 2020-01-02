
#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "glm/glm.hpp"
#include <iostream>
#include <string>



class BaseObject
{

private:
    
    glm::mat4 m_Proj, m_View, m_model;
    glm::vec3 m_Translation;
    float m_Rotation;
    float m_Color[4];

    std::string m_Name;

public:
    BaseObject(std::string name, float posX, float posY);
    ~BaseObject();

    glm::vec3* GetTranslation() { return &m_Translation; };
    inline void SetTranslation(glm::vec3 translation) { m_Translation = translation; };
    inline float* GetColors() { return m_Color; };
    inline std::string GetName() { return m_Name; };
    


};

#endif
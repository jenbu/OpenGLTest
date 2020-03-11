#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "imgui/imgui.h"
#include "glm/glm.hpp"

enum MenuSubElement
{
    Button = 0,
    InputFloat3,
    InputInt3,
    InputInt2,
    InputDouble
};

class SubElementBase
{
public:

    virtual bool Draw() {};
    virtual std::string ElementName() {};
};

template<MenuSubElement e> 
class ImGuiMenuElement : public SubElementBase {};

template<>
class ImGuiMenuElement<MenuSubElement::Button> : public SubElementBase
{
public:
    ImGuiMenuElement(std::string name, bool *pressed)
    {
        if(pressed == NULL)
        {
            m_OutPut = false;

        }
        else
        {
            m_OutPut = true;
            m_Pressed = pressed;
        }
        

        
        m_Name = name;
    }

    bool Draw() override
    {
        if(m_OutPut)
            *m_Pressed = false;

        if(ImGui::Button(m_Name.c_str()))
        {
            if(m_OutPut)
                *m_Pressed = true;
            
            return true;
        }

        return false;
    }

    std::string ElementName() override
    {
        return m_Name;
    }

private:
    std::string m_Name;
    bool *m_Pressed;
    bool m_OutPut;
};

template<>
class ImGuiMenuElement<MenuSubElement::InputFloat3> : public SubElementBase
{
public:
    ImGuiMenuElement(std::string name, glm::vec3* arr)
    {
        m_Name = name;
        m_Arr = arr;
    }

    bool Draw()
    {
        return ImGui::InputFloat3(m_Name.c_str(), &m_Arr->x);
    }

    std::string ElementName() override
    {
        return m_Name;
    }


private:
    std::string m_Name;
    glm::vec3* m_Arr;
};

template<>
class ImGuiMenuElement<MenuSubElement::InputInt3> : public SubElementBase
{
public:
    ImGuiMenuElement(std::string name, glm::ivec3* arr)
    {
        m_Name = name;
        m_Arr = arr;
    }

    bool Draw()
    {
        return ImGui::InputInt3(m_Name.c_str(), &m_Arr->x);
    }

    std::string ElementName() override
    {
        return m_Name;
    }


private:
    std::string m_Name;
    glm::ivec3* m_Arr;
};

template<>
class ImGuiMenuElement<MenuSubElement::InputDouble> : public SubElementBase
{
public:
    ImGuiMenuElement(std::string name, double *val)
    {
        m_DoubleVal = val;
        m_Name = name;
    }

    bool Draw() override
    {
        return ImGui::InputDouble(m_Name.c_str(), m_DoubleVal);
    }

    std::string ElementName() override
    {
        return m_Name;
    }

private:
    std::string m_Name;
    double *m_DoubleVal;
};

template<>
class ImGuiMenuElement<MenuSubElement::InputInt2> : public SubElementBase
{
public:
    ImGuiMenuElement(std::string name, glm::ivec2* val)
    {
        m_IntVec2 = val;
        m_Name = name;
    }

    bool Draw() override
    {
        return ImGui::InputInt2(m_Name.c_str(), &m_IntVec2->x);
    }

    std::string ElementName() override
    {
        return m_Name;
    }

private:
    std::string m_Name;
    glm::ivec2 *m_IntVec2;
};
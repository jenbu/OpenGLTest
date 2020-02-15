#pragma once

#include <vector>

#include "ImGuiSubMenu.h"
#include "imgui/imgui.h"



class ImGuiMenu
{
private:
    unsigned int m_NumPages;
    std::vector <ImGuiSubMenu> m_SubMenu;
public:
    ImGuiMenu(/* args */);
    ~ImGuiMenu();

    void AddSubMenu();
};


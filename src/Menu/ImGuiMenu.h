#pragma once

#include <vector>
#include <string>
#include <utility>

//#include "ImGuiMenuElement.h"
#include "ImGuiSubMenu.h"
//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_glfw_gl3.h"
#include "glm/glm.hpp"

class ImGuiMenu
{
private:
    std::string m_MenuName;
    unsigned int m_NumPages;
    
    std::vector<ImGuiSubMenu*> m_SubMenus;
    ImGuiSubMenu* m_CurrentSubMenu;
    ImGuiSubMenu* m_MainMenu;
    
public:
    ImGuiMenu(std::string name);
    ~ImGuiMenu();

    bool MenuDraw();
    bool AddSubMenu(ImGuiSubMenu* subMenu);
};


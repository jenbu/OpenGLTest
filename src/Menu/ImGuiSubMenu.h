#pragma once

#include <vector>
#include <string>
#include <memory>

#include "ImGuiMenuElement.h"

class ImGuiSubMenu
{
public:
    ImGuiSubMenu(std::string subname);
    ~ImGuiSubMenu();

    inline unsigned int GetId() { return m_ID; }
    inline std::string GetName() { return m_Name; }

    bool SubMenuAddElement(SubElementBase* element, ImGuiSubMenu* menu = NULL);
    ImGuiSubMenu* DrawSubMenu();

    static unsigned int subMenuID;

private:
    unsigned int m_ID;
    std::string m_Name;
    std::vector<std::pair<SubElementBase*, ImGuiSubMenu*>> m_MenuElements;

};
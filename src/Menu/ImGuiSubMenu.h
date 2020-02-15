#pragma once

enum MenuType
{
    MainMenu = 0,
    AddObject
};

class ImGuiSubMenu
{
public:
    ImGuiSubMenu(MenuType type);
    ~ImGuiSubMenu();


    bool m_Active;


};

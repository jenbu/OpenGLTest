#include "ImGuiMenu.h"

ImGuiMenu::ImGuiMenu(std::string name)
: m_NumPages(0), m_MenuName(name)
{
    m_MainMenu = new ImGuiSubMenu("Main Menu");
    m_CurrentSubMenu = m_MainMenu;
}

ImGuiMenu::~ImGuiMenu()
{
    std::cout << "ImGuiMenu destructor" << std::endl;
    for(std::vector<ImGuiSubMenu*>::iterator it = m_SubMenus.begin(); it != m_SubMenus.end(); it++)
    {
        delete *(it);
    }
    delete m_CurrentSubMenu, m_MainMenu;
}


bool ImGuiMenu::AddSubMenu(ImGuiSubMenu* subMenu)
{    
    m_SubMenus.push_back(subMenu);
}

bool ImGuiMenu::MenuDraw()
{
    ImGuiSubMenu* temp = NULL;
    if(m_SubMenus.size() < 1)
    {
        std::cout << "No submenus to draw!" << std::endl;
        return false;
    }

    //ImGui::Begin(m_MenuName.c_str());

    if(m_CurrentSubMenu != m_MainMenu)
    {
        if(ImGui::Button("Back"))
            m_CurrentSubMenu = m_MainMenu;

        temp = m_CurrentSubMenu->DrawSubMenu();
        if(temp != NULL)
            m_CurrentSubMenu = temp;
    }
    else //main menu
    {
        for(int i = 0; i < m_SubMenus.size(); i++)
        {
            if(ImGui::Button(m_SubMenus[i]->GetName().c_str()))
            {
                m_CurrentSubMenu = m_SubMenus[i];
            }
        }

    }
    




    //ImGui::End();
    
    return true;
}
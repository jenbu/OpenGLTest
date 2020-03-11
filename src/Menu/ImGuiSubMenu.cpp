#include "ImGuiSubMenu.h"

unsigned int ImGuiSubMenu::subMenuID = 1;

ImGuiSubMenu::ImGuiSubMenu(std::string subname)
: m_Name(subname)
{
    m_ID = subMenuID;
    subMenuID++;
}

ImGuiSubMenu::~ImGuiSubMenu()
{
    std::cout << "ImGuiSubMenu destructor" << std::endl;
    for(std::vector<std::pair<SubElementBase*, ImGuiSubMenu*>>::iterator it = m_MenuElements.begin(); it != m_MenuElements.end(); it++)
    {
        delete (*it).first, (*it).second;
    }
}

bool ImGuiSubMenu::SubMenuAddElement(SubElementBase* element, ImGuiSubMenu* menu)
{
    m_MenuElements.push_back(std::pair<SubElementBase*, ImGuiSubMenu*> (element, menu)); 
}

ImGuiSubMenu* ImGuiSubMenu::DrawSubMenu()
{

    if(m_MenuElements.size() < 1)
        return NULL;

    for(int i = 0; i < m_MenuElements.size(); i++)
    {
        if(m_MenuElements[i].first->Draw())
        {
            std::cout << "Element " << m_MenuElements[i].first->ElementName() << " pressed!" << std::endl;
            if(m_MenuElements[i].second != NULL)
                return m_MenuElements[i].second;

        }
    }

    return NULL;
}
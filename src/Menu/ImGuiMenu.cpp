#include "ImGuiMenu.h"

ImGuiMenu::ImGuiMenu()
: m_NumPages(0)
{
}

ImGuiMenu::~ImGuiMenu()
{
}

void ImGuiMenu::AddSubMenu()
{
    ++m_NumPages;

}
#include "gui_interaction.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

GuiInteraction::GuiInteraction(): m_active{true}
{

}

GuiInteraction::GuiInteraction(bool active): m_active{active}
{

}

GuiInteraction::~GuiInteraction() noexcept
{

}

GuiInteraction::GuiInteraction(const GuiInteraction& other): m_colliders{other.m_colliders}, m_active{other.m_active}
{

}

GuiInteraction::GuiInteraction(GuiInteraction&& other) noexcept
{

}

GuiInteraction& GuiInteraction::operator=(const GuiInteraction& other)
{
    // if(this != &other)//not same ref
    // {
    //     GuiInteraction tmp(other);
    //     *this = std::move(tmp);
    // }

    return *this;
}

GuiInteraction& GuiInteraction::operator=(GuiInteraction&& other) noexcept
{
    return *this;
}

/* Add Box collider */
void GuiInteraction::AddGuiCollider(const SDL_Rect& collider_dimensions)
{
    m_colliders.emplace(std::end(m_colliders), GuiCollider(collider_dimensions));
}
/* Add Circle collider */
void GuiInteraction::AddGuiCollider(int centre_x, int centre_y, int circle_radius)
{
    m_colliders.emplace(std::end(m_colliders), GuiCollider(centre_x, centre_y, circle_radius));
}

bool GuiInteraction::MouseInsideCollider(int mouse_x, int mouse_y)
{
    for(GuiCollider& collider : m_colliders)
    {
        if(collider.IsPointColliding(mouse_x, mouse_y))
            return true;
    }
    return false;
}

}//namespace

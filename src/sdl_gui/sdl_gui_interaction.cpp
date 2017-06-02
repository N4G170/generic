#include "sdl_gui_interaction.hpp"
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
    m_active = std::move(other.m_active);
}

GuiInteraction& GuiInteraction::operator=(const GuiInteraction& other)
{
    m_active = other.m_active;

    return *this;
}

GuiInteraction& GuiInteraction::operator=(GuiInteraction&& other) noexcept
{
    m_active = std::move(other.m_active);
    return *this;
}

void GuiInteraction::Input(const SDL_Event& event)
{

}

void GuiInteraction::ClearInput()
{
    m_mouse_flags = MouseFlags::NONE;
}

void GuiInteraction::CallBacksLogic(float delta_time)
{
    if(m_active)
    {
        m_valid_click_timer += delta_time;

        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
        {
            for(auto& callback : m_mouse_hover_callbacks)
                callback();
        }
        if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
        {
            m_valid_click_timer = 0;//start click timer

            m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
            for(auto& callback : m_mouse_down_callbacks)
                callback();
        }
        else if(m_mouse_flags & MouseFlags::MOUSE_UP)
        {
            m_mouse_flags &= ~MouseFlags::MOUSE_UP;
            for(auto& callback : m_mouse_up_callbacks)
                callback();

            if(m_valid_click_timer <= 0.1)
            {
                for(auto& callback : m_mouse_click_callbacks)
                    callback();
            }
        }

        if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
        {
            for(auto& callback : m_mouse_hold_callbacks)
                callback();
        }
    }
}

/* Add Box collider */
void GuiInteraction::AddGuiCollider(const Position& position, const Dimensions& dimensions, GuiTransform* owner_transform)
{
    m_colliders.emplace(std::end(m_colliders), Collider(position, dimensions, owner_transform));
}
/* Add Circle collider */
void GuiInteraction::AddGuiCollider(const Position& position, int circle_radius, GuiTransform* owner_transform)
{
    m_colliders.emplace(std::end(m_colliders), Collider(position, circle_radius, owner_transform));
}

bool GuiInteraction::MouseInsideCollider(int mouse_x, int mouse_y)
{
    for(Collider& collider : m_colliders)
    {
        if(collider.IsPointColliding(mouse_x, mouse_y))
            return true;
    }
    return false;
}

}//namespace

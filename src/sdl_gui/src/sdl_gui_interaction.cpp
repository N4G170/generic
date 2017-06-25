#include "sdl_gui_interaction.hpp"
#include <utility>
#include "sdl_gui_log.hpp"
#include "sdl_gui_utf8.hpp"

namespace sdl_gui
{

IGuiInteraction::IGuiInteraction(): m_active{true}, m_under_focus{false}, m_mouse_flags{MouseFlags::NONE}, m_valid_click_timer{10}
{

}

IGuiInteraction::IGuiInteraction(bool active): m_active{active}, m_under_focus{false}, m_mouse_flags{MouseFlags::NONE}, m_valid_click_timer{10}
{

}

IGuiInteraction::~IGuiInteraction() noexcept
{

}

IGuiInteraction::IGuiInteraction(const IGuiInteraction& other): m_colliders{other.m_colliders}, m_active{other.m_active}, m_under_focus{other.m_under_focus},
    m_mouse_flags{other.m_mouse_flags}, m_valid_click_timer{other.m_valid_click_timer}
{

}

IGuiInteraction::IGuiInteraction(IGuiInteraction&& other) noexcept
{
    m_active = std::move(other.m_active);
}

IGuiInteraction& IGuiInteraction::operator=(const IGuiInteraction& other)
{
    m_colliders = other.m_colliders;
    m_active = other.m_active;
    m_under_focus = other.m_under_focus;

    m_mouse_flags = other.m_mouse_flags;
    m_valid_click_timer = other.m_valid_click_timer;

    return *this;
}

IGuiInteraction& IGuiInteraction::operator=(IGuiInteraction&& other) noexcept
{
    m_colliders = std::move(other.m_colliders);
    m_active = std::move(other.m_active);
    m_under_focus = std::move(other.m_under_focus);

    m_mouse_flags = std::move(other.m_mouse_flags);
    m_valid_click_timer = std::move(other.m_valid_click_timer);
    return *this;
}

void IGuiInteraction::Input(const SDL_Event& event)
{

}

void IGuiInteraction::ClearInput()
{
    m_mouse_flags = MouseFlags::NONE;
}

void IGuiInteraction::CallBacksLogic(float delta_time)
{
    if(m_active)
    {
        if(m_mouse_callbacks[MouseCallbackType::ACTIVE])
            m_mouse_callbacks[MouseCallbackType::ACTIVE]();

        m_valid_click_timer += delta_time;

        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
        {
            if(m_mouse_callbacks[MouseCallbackType::HOVER])
                m_mouse_callbacks[MouseCallbackType::HOVER]();
        }
        if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
        {
            m_valid_click_timer = 0;//start click timer

            m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
            if(m_mouse_callbacks[MouseCallbackType::DOWN])
                m_mouse_callbacks[MouseCallbackType::DOWN]();
        }
        else if(m_mouse_flags & MouseFlags::MOUSE_UP)
        {
            m_mouse_flags &= ~MouseFlags::MOUSE_UP;
            if(m_mouse_callbacks[MouseCallbackType::UP])
                m_mouse_callbacks[MouseCallbackType::UP]();

            if(m_valid_click_timer <= 0.25)
            {
                if(m_mouse_callbacks[MouseCallbackType::CLICK])
                    m_mouse_callbacks[MouseCallbackType::CLICK]();
            }
        }

        if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
        {
            if(m_mouse_callbacks[MouseCallbackType::HOLD])
                m_mouse_callbacks[MouseCallbackType::HOLD]();
        }
    }
    else
    {
        if(m_mouse_callbacks[MouseCallbackType::INACTIVE])
            m_mouse_callbacks[MouseCallbackType::INACTIVE]();
    }
}

/* Add Box collider */
void IGuiInteraction::AddGuiCollider(const Position& position, const Dimensions& dimensions, GuiTransform* owner_transform)
{
    m_colliders.emplace(std::end(m_colliders), Collider(position, dimensions, owner_transform));
}
/* Add Circle collider */
void IGuiInteraction::AddGuiCollider(const Position& position, int circle_radius, GuiTransform* owner_transform)
{
    m_colliders.emplace(std::end(m_colliders), Collider(position, circle_radius, owner_transform));
}

bool IGuiInteraction::MouseInsideCollider(int mouse_x, int mouse_y)
{
    for(Collider& collider : m_colliders)
    {
        if(collider.IsPointColliding(mouse_x, mouse_y))
            return true;
    }
    return false;
}

}//namespace

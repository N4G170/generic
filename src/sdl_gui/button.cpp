#include "button.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

Button::Button(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions): GuiElement{renderer_ptr, position, dimensions}, m_transition_type{TransitionType::COLOUR},
m_current_image{nullptr}, m_current_colour{0,0,0,0}, m_mouse_flags{0}, m_allow_click{false}
{
    AddGuiCollider({ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h });
    // m_image = new GuiImage(renderer_ptr, "data/img/bg.png");
    // m_image->Parent(this);
    // m_label_ptr = new Label(renderer_ptr, "data/font/DejaVuSansMono.ttf", 15, "string", {255, 255, 255,255}, {15, 15}, {-1, -1});

    m_status_colours.insert({ButtonStatus::ACTIVE, {255,255,255,255}});
    m_status_colours.insert({ButtonStatus::INACTIVE, {255,255,255,128}});
    m_status_colours.insert({ButtonStatus::HOVER, {200,200,200,255}});
    m_status_colours.insert({ButtonStatus::DOWN, {145,145,145,255}});
}

Button::~Button() noexcept
{

}

Button::Button(const Button& other): GuiElement{other}, GuiInteraction{other},
m_status_colours{other.m_status_colours}, m_transition_type{other.m_transition_type}, m_current_image{other.m_current_image},
m_current_colour{other.m_current_colour}, m_mouse_flags{other.m_mouse_flags}, m_allow_click{other.m_allow_click}
{

}

Button::Button(Button&& other) noexcept
{

}

Button& Button::operator=(const Button& other)
{
    if(this != &other)//not same ref
    {
        Button tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Button& Button::operator=(Button&& other) noexcept
{
    return *this;
}

/* < Overrides GUIElement > */
void Button::Logic()
{
    if(m_active)
    {
        m_current_colour = m_status_colours[ButtonStatus::ACTIVE];

        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
            m_current_colour = m_status_colours[ButtonStatus::HOVER];
        if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
            m_current_colour = m_status_colours[ButtonStatus::DOWN];
    }
    else
    {
        m_current_colour = m_status_colours[ButtonStatus::INACTIVE];
    }
}

void Button::Render()
{
    SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    // SDL_Rect dst{ 150, 150, 150, 150 };
    SDL_SetRenderDrawColor(m_renderer_ptr, m_current_colour.r, m_current_colour.g, m_current_colour.b, m_current_colour.a);
    SDL_RenderFillRect(m_renderer_ptr, &dst);
}

void Button::Render(SDL_Renderer* renderer)
{
    SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    // SDL_RenderCopy(renderer, m_text_texture, nullptr, &dst);

}
/* </ Overrides > */

/* < Overrides GuiInteraction > */
void Button::Input(const SDL_Event &event)
{
    if( !m_active )
        return;

    bool status{ MouseInsideCollider(event.motion.x, event.motion.y) };

    //clear flags before starting new cycle
    // m_mouse_flags &= ~MouseFlags::MOUSE_HOVER;//remove
    // m_mouse_flags &= ~MouseFlags::MOUSE_EXIT;//remove
    // m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;//remove
    m_mouse_flags = MouseFlags::NONE;

    if(!(m_mouse_flags & MouseFlags::MOUSE_HOVER) && status)//we enter the button
        m_mouse_flags |= MouseFlags::MOUSE_ENTER;//add
    if((m_mouse_flags & MouseFlags::MOUSE_HOVER) && !status)//we exit the button
        m_mouse_flags |= MouseFlags::MOUSE_EXIT;//add

    if(status)//hover
        m_mouse_flags |= MouseFlags::MOUSE_HOVER;//add
    else
        m_mouse_flags &= ~MouseFlags::MOUSE_HOVER;//remove

    if((m_mouse_flags & MouseFlags::MOUSE_HOVER) && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)//valid btn down
    {
        std::cout << "CLICK" << "\n";
        m_mouse_flags |= MouseFlags::MOUSE_DOWN;
    }
}
/* </ Overrides > */

}//namespace

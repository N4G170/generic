#include "button.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

Button::Button(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions): GuiElement{renderer_ptr, position, dimensions}
{
    AddGuiCollider({ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h });
    m_image = new GuiImage(renderer_ptr, "data/img/bg.png", {150, 5});
    m_label_ptr = new Label(renderer_ptr, "data/font/DejaVuSansMono.ttf", 15, "string", {0,0,0,255}, {15, 15}, {-1, -1});
}

Button::~Button() noexcept
{

}

Button::Button(const Button& other)
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
void Button::Render()
{
    // SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    SDL_Rect dst{ 15,15,150,150 };
    // SDL_RenderCopy(m_renderer_ptr, m_text_texture, nullptr, &dst);
    SDL_SetRenderDrawColor(m_renderer_ptr, 128, 128, 128, 255);
    SDL_RenderDrawRect(m_renderer_ptr, &dst);

    m_image->Render();
    m_label_ptr->Render();
}

void Button::Render(SDL_Renderer* renderer)
{
    SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    // SDL_RenderCopy(renderer, m_text_texture, nullptr, &dst);

    m_image->Render(renderer);
}

void Button::Logic()
{
    // c = Colour::Black;//default
    //
    // if(m_mouse_hover)
    //     c = Colour::Light_Blue;
    // if(m_mouse_down)
    //     c = Colour::Blue;
}
/* </ Overrides > */

/* < Overrides GuiInteraction > */
void Button::Input(const SDL_Event &event)
{
    bool status{ MouseInsideCollider(event.motion.x, event.motion.y) };

    //clear flags before starting new cycle
    m_mouse_enter = false;
    m_mouse_exit = false;
    m_mouse_down = false;

    if(!m_mouse_hover && status)//we enter the button
        m_mouse_enter = true;
    if(m_mouse_hover && !status)//we exit the button
        m_mouse_exit = true;

    m_mouse_hover = status;

    if(m_mouse_hover && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)//valid btn down
    {
        m_mouse_down = true;
    }
}
/* </ Overrides > */

}//namespace

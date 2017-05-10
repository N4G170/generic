#include "gui_element.hpp"
#include <utility>

namespace sdl_gui
{

GuiElement::GuiElement(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions): m_position{position}, m_dimensions{dimensions}, m_z_index{0},
    m_renderer_ptr{renderer_ptr}, m_parent{nullptr}
{

}

GuiElement::GuiElement():  m_position{}, m_dimensions{}, m_z_index{0},
    m_renderer_ptr{nullptr}, m_parent{nullptr}
{

}

GuiElement::~GuiElement() noexcept
{

}

GuiElement::GuiElement(const GuiElement& other):  m_position{other.m_position}, m_dimensions{other.m_dimensions}, m_z_index{other.m_z_index},
    m_renderer_ptr{other.m_renderer_ptr}, m_parent{other.m_parent}
{
    
}

GuiElement::GuiElement(GuiElement&& other) noexcept
{

}

GuiElement& GuiElement::operator=(const GuiElement& other)
{
    // if(this != &other)//not same ref
    // {
    //     GuiElement tmp(other);
    //     *this = std::move(tmp);
    // }

    return *this;
}

GuiElement& GuiElement::operator=(GuiElement&& other) noexcept
{
    return *this;
}

}//namespace

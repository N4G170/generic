#include "gui_element.hpp"
#include <utility>

namespace sdl_gui
{

GuiElement::GuiElement(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions): m_position{position}, m_dimensions{dimensions}, m_renderer_ptr{nullptr}
{

}

GuiElement::GuiElement(): m_position{}, m_dimensions{}, m_renderer_ptr{nullptr}
{

}

GuiElement::~GuiElement() noexcept
{

}

GuiElement::GuiElement(const GuiElement& other)
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

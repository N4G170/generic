#include "sdl_gui_element.hpp"
#include <utility>

namespace sdl_gui
{

GuiElement::GuiElement(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position local_position, Dimensions dimensions): m_transform{}, m_z_index{0},
    m_render_bounds_border{false}, m_resource_manager_ptr{resource_manager_ptr}, m_renderer_ptr{renderer_ptr}
{
    m_transform.LocalPosition(local_position);
    m_transform.BaseDimensions(dimensions);
}

GuiElement::GuiElement():  m_transform{}, m_z_index{0}, m_render_bounds_border{false},
    m_resource_manager_ptr{nullptr}, m_renderer_ptr{nullptr}
{

}

GuiElement::~GuiElement() noexcept
{

}

GuiElement::GuiElement(const GuiElement& other):  m_transform{other.m_transform}, m_z_index{other.m_z_index}, m_render_bounds_border{other.m_render_bounds_border},
    m_resource_manager_ptr{other.m_resource_manager_ptr}, m_renderer_ptr{other.m_renderer_ptr}
{

}

GuiElement::GuiElement(GuiElement&& other) noexcept
{
    m_transform = std::move(other.m_transform);

    // AnchorType m_anchor_type;
    m_render_bounds_border = std::move(other.m_render_bounds_border);
    m_z_index = std::move(other.m_z_index);

    m_resource_manager_ptr = std::move(other.m_resource_manager_ptr);
    m_renderer_ptr = std::move(other.m_renderer_ptr);
}

void GuiElement::RenderBorder()
{
    SDL_Rect border = m_transform.RenderRect();
    SDL_SetRenderDrawColor(m_renderer_ptr, m_border_colour.r, m_border_colour.g, m_border_colour.b, m_border_colour.a);
    SDL_RenderDrawRect(m_renderer_ptr, &border);
};

}//namespace

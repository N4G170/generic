#include "sdl_gui_render.hpp"
#include <utility>

namespace sdl_gui
{

//<f> Constructors & operator=
IGuiRender::IGuiRender(): m_renderer_ptr{nullptr}, m_resource_manager_ptr{nullptr},
    m_render{true}, m_zindex{0}, m_render_border{false}, m_border_colour{0,0,0,255}, m_border_rect{0,0,0,0}
{

}

IGuiRender::IGuiRender(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr): m_renderer_ptr{renderer_ptr}, m_resource_manager_ptr{resource_manager_ptr},
    m_render{true}, m_zindex{0}, m_render_border{false}, m_border_colour{0,0,0,255}, m_border_rect{0,0,0,0}
{

}

IGuiRender::~IGuiRender() noexcept
{
    m_renderer_ptr = nullptr;
}

IGuiRender::IGuiRender(const IGuiRender& other): m_renderer_ptr{other.m_renderer_ptr},  m_resource_manager_ptr{other.m_resource_manager_ptr},
    m_render{other.m_render}, m_zindex{other.m_zindex}, m_render_border{other.m_render_border}, m_border_colour{other.m_border_colour}, m_border_rect{other.m_border_rect}
{}

IGuiRender::IGuiRender(IGuiRender&& other) noexcept : m_renderer_ptr{std::move(other.m_renderer_ptr)},  m_resource_manager_ptr{std::move(other.m_resource_manager_ptr)},
    m_render{std::move(other.m_render)}, m_zindex{std::move(other.m_zindex)},
    m_render_border{std::move(other.m_render_border)}, m_border_colour{std::move(other.m_border_colour)}, m_border_rect{std::move(other.m_border_rect)}
{}

IGuiRender& IGuiRender::operator=(const IGuiRender& other)
{
    if(this != &other)//different objects
    {
        this->m_renderer_ptr = other.m_renderer_ptr;
        this->m_resource_manager_ptr = other.m_resource_manager_ptr;
        this->m_render = other.m_render;
        this->m_zindex = other.m_zindex;
        this->m_render_border = other.m_render_border;
        this->m_border_colour = other.m_border_colour;
        this->m_border_rect = other.m_border_rect;
    }
    return *this;
}

IGuiRender& IGuiRender::operator=(IGuiRender&& other) noexcept
{
    if(this != &other)//different objects
    {
        this->m_renderer_ptr = std::move(other.m_renderer_ptr);
        this->m_resource_manager_ptr = std::move(other.m_resource_manager_ptr);
        this->m_render = std::move(other.m_render);
        this->m_zindex = std::move(other.m_zindex);
        this->m_render_border = std::move(other.m_render_border);
        this->m_border_colour = std::move(other.m_border_colour);
        this->m_border_rect = std::move(other.m_border_rect);
    }
    return *this;
}
//</f>

//<f> Virtual Methods
void IGuiRender::RenderBorder(float delta_time)
{
    SDL_SetRenderDrawColor(m_renderer_ptr, m_border_colour.r, m_border_colour.g, m_border_colour.b, m_border_colour.a);
    SDL_RenderDrawRect(m_renderer_ptr, &m_border_rect);
}
//</f>

}

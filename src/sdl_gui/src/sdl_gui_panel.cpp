#include "sdl_gui_panel.hpp"
#include <utility>
#include "SDL_image.h"
#include <iostream>

namespace sdl_gui
{

Panel::Panel(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, const std::string& texture_path): GuiElement{ {0,0}, {0,0}}
{
    // m_texture = SDL_CreateTextureFromSurface(renderer_ptr, IMG_Load(texture_path.data()));
    m_source_rect.reset();
}

Panel::~Panel() noexcept
{

    m_source_rect.reset();
}

Panel::Panel(const Panel& other)
{

}

Panel::Panel(Panel&& other) noexcept
{

}

Panel& Panel::operator=(const Panel& other)
{
    if(this != &other)//not same ref
    {
        Panel tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Panel& Panel::operator=(Panel&& other) noexcept
{
    return *this;
}

/* < Overrides GUIElement > */
void Panel::Logic(float fixed_delta_time)
{

}

void Panel::Render(float delta_time)
{
    // if(m_has_destination_rect)
    // {
    //     SDL_Rect dst{ m_transform.RenderRect() };
    //     SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), &dst);
    // }
    // else
    //     SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}

void Panel::Render(SDL_Renderer* renderer_ptr, float delta_time)
{
    // if(m_has_destination_rect)
    // {
    //     SDL_Rect dst{ m_transform.RenderRect() };
    //     SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), &dst);
    // }
    // else
    //     SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}
/* </ Overrides > */

void Panel::SetSourceRect(SDL_Rect src_rect)
{
    m_source_rect.reset(new SDL_Rect{src_rect});
}

void Panel::ClearSourceRect()
{
    m_source_rect.reset();
}

void Panel::SetDestinationRect(SDL_Rect dst_rect)
{
    // m_transform.X(dst_rect.x);
    // m_position.y = dst_rect.y;
    // m_dimensions.w = dst_rect.w;
    // m_dimensions.h = dst_rect.h;
}

void Panel::ClearDestinationRect()
{
    if(m_transform.Parent() != nullptr)
    {
        std::cout << "asd" << "\n";
        // m_position.x = m_parent->X();
        // m_position.y = m_parent->Y();
        // m_dimensions.w = m_parent->Width();
        // m_dimensions.h = m_parent->Height();
    }
    else
    {
        // m_has_destination_rect = false;
    }
}

}//namespace

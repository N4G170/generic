#include "sdl_gui_image.hpp"
#include <utility>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace sdl_gui
{

Image::Image(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, const std::string& texture_path): GuiElement{resource_manager_ptr, renderer_ptr, {0,0}, {0,0}}, m_has_destination_rect{false}
{
    m_texture = SDL_CreateTextureFromSurface(renderer_ptr, IMG_Load(texture_path.data()));
    m_source_rect.reset();
}

Image::~Image() noexcept
{
    if(m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    m_source_rect.reset();
}

Image::Image(const Image& other)
{

}

Image::Image(Image&& other) noexcept
{

}

Image& Image::operator=(const Image& other)
{
    if(this != &other)//not same ref
    {
        Image tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
    return *this;
}

/* < Overrides GUIElement > */
void Image::Logic(float fixed_delta_time)
{

}

void Image::Render(float delta_time)
{
    if(m_has_destination_rect)
    {
        SDL_Rect dst{ m_transform.RenderRect() };
        SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), &dst);
    }
    else
        SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}

void Image::Render(SDL_Renderer* renderer_ptr, float delta_time)
{
    if(m_has_destination_rect)
    {
        SDL_Rect dst{ m_transform.RenderRect() };
        SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), &dst);
    }
    else
        SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}
/* </ Overrides > */

void Image::SetSourceRect(SDL_Rect src_rect)
{
    m_source_rect.reset(new SDL_Rect{src_rect});
}

void Image::ClearSourceRect()
{
    m_source_rect.reset();
}

void Image::SetDestinationRect(SDL_Rect dst_rect)
{
    // m_transform.X(dst_rect.x);
    // m_position.y = dst_rect.y;
    // m_dimensions.w = dst_rect.w;
    // m_dimensions.h = dst_rect.h;
    m_has_destination_rect = true;
}

void Image::ClearDestinationRect()
{
    if(m_transform.Parent() != nullptr)
    {
        std::cout << "asd" << "\n";
        // m_position.x = m_parent->X();
        // m_position.y = m_parent->Y();
        // m_dimensions.w = m_parent->Width();
        // m_dimensions.h = m_parent->Height();
        m_has_destination_rect = true;
    }
    else
    {
        m_has_destination_rect = false;
    }
}

}//namespace

#include "gui_image.hpp"
#include <utility>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace sdl_gui
{

GuiImage::GuiImage(SDL_Renderer* renderer_ptr, const std::string& texture_path): GuiElement{renderer_ptr, {0,0}, {0,0}}, m_has_destination_rect{false}
{
    m_texture = SDL_CreateTextureFromSurface(renderer_ptr, IMG_Load(texture_path.data()));
    m_source_rect.reset();
}

GuiImage::~GuiImage() noexcept
{
    if(m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    m_source_rect.reset();
}

GuiImage::GuiImage(const GuiImage& other)
{

}

GuiImage::GuiImage(GuiImage&& other) noexcept
{

}

GuiImage& GuiImage::operator=(const GuiImage& other)
{
    if(this != &other)//not same ref
    {
        GuiImage tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiImage& GuiImage::operator=(GuiImage&& other) noexcept
{
    return *this;
}

/* < Overrides GUIElement > */
void GuiImage::Logic()
{

}

void GuiImage::Render()
{
    if(m_has_destination_rect)
    {
        SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
        SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), &dst);
    }
    else
        SDL_RenderCopy(m_renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}

void GuiImage::Render(SDL_Renderer* renderer_ptr)
{
    if(m_has_destination_rect)
    {
        SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
        SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), &dst);
    }
    else
        SDL_RenderCopy(renderer_ptr, m_texture, m_source_rect.get(), nullptr);
}
/* </ Overrides > */

void GuiImage::SetSourceRect(SDL_Rect src_rect)
{
    m_source_rect.reset(new SDL_Rect{src_rect});
}

void GuiImage::ClearSourceRect()
{
    m_source_rect.reset();
}

void GuiImage::SetDestinationRect(SDL_Rect dst_rect)
{
    // m_transform.X(dst_rect.x);
    // m_position.y = dst_rect.y;
    // m_dimensions.w = dst_rect.w;
    // m_dimensions.h = dst_rect.h;
    m_has_destination_rect = true;
}

void GuiImage::ClearDestinationRect()
{
    if(m_parent)
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

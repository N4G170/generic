#include "sdl_gui_texture.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

Texture::Texture():m_renderer_ptr{nullptr}, m_texture_ptr{nullptr}, m_src_rect{nullptr},
    m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{

}

Texture::Texture(SDL_Renderer* renderer_ptr, SDL_Texture* texture_ptr):m_renderer_ptr{renderer_ptr}, m_texture_ptr{texture_ptr}, m_src_rect{nullptr},
    m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{

}

Texture::~Texture() noexcept
{
    /* This class does not own the renderer ptr, so DO NOT DELETE IT */

    ClearSourceRect();
    ClearDestinationRect();
}

Texture::Texture(const Texture& other): m_renderer_ptr{other.m_renderer_ptr}, m_texture_ptr{other.m_texture_ptr}, m_src_rect{other.m_src_rect},
    m_dst_rect{other.m_dst_rect}, m_colour_modulation{other.m_colour_modulation}
{

}

Texture::Texture(Texture&& other) noexcept
{
    m_renderer_ptr = std::move(other.m_renderer_ptr);
    m_texture_ptr = std::move(other.m_texture_ptr);

    m_src_rect = std::move(other.m_src_rect);
    m_dst_rect = std::move(other.m_dst_rect);

    m_colour_modulation = std::move(other.m_colour_modulation);
}

Texture& Texture::operator=(const Texture& other)
{
    if(this != &other)//not same ref
    {
        Texture tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    this->m_renderer_ptr = std::move(other.m_renderer_ptr);
    this->m_texture_ptr = std::move(other.m_texture_ptr);

    this->m_src_rect = std::move(other.m_src_rect);
    this->m_dst_rect = std::move(other.m_dst_rect);
    this->m_colour_modulation = std::move(other.m_colour_modulation);

    return *this;
}

void Texture::SourceRect(SDL_Rect src_rect)
{
    if(m_src_rect == nullptr)
    {
        m_src_rect = new SDL_Rect{src_rect};
    }
    else
    {
        *m_src_rect = src_rect;
    }
}

void Texture::DestinationRect(SDL_Rect dst_rect)
{
    if(m_dst_rect == nullptr)
    {
        m_dst_rect = new SDL_Rect{dst_rect};
    }
    else
    {
        *m_dst_rect = dst_rect;
    }
}

void Texture::ClearSourceRect()
{
    delete(m_src_rect);
    m_src_rect = nullptr;
}

void Texture::ClearDestinationRect()
{
    delete(m_dst_rect);
    m_dst_rect = nullptr;
}

void Texture::Render()
{
    Render(m_src_rect, m_dst_rect);
}

void Texture::Render(SDL_Rect* src_rect, SDL_Rect* dst_rect)
{
    if(m_texture_ptr == nullptr)
        return;

    SDL_SetTextureAlphaMod(m_texture_ptr, m_colour_modulation.a);
    SDL_SetTextureColorMod(m_texture_ptr, m_colour_modulation.r, m_colour_modulation.g, m_colour_modulation.b);
    SDL_RenderCopy(m_renderer_ptr, m_texture_ptr, src_rect, dst_rect);
    //we reset the alpha and color modulation after rendering as the texture may be shared
    SDL_SetTextureColorMod(m_texture_ptr, 255, 255, 255);
    SDL_SetTextureAlphaMod(m_texture_ptr, 255);
}

}//namespace

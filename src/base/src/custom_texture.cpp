#include "custom_texture.hpp"
#include <utility>
#include <iostream>
#include "texture_utils.hpp"
#include "vector3_utils.hpp"

CustomTexture::CustomTexture() : m_renderer{nullptr}, m_texture{nullptr}, m_src_rect{nullptr},
    m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{

}

CustomTexture::CustomTexture(SDL_Renderer* renderer_ptr, int w, int h) : m_renderer{renderer_ptr}, m_texture{nullptr}, m_src_rect{nullptr},
    m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{
    m_texture.reset(SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h));
}

CustomTexture::CustomTexture(SDL_Renderer* renderer_ptr, const Vector3<float>& size) : m_renderer{renderer_ptr}, m_texture{nullptr}, m_src_rect{nullptr},
    m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{
    m_texture.reset(SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CoordinateToInt(size.X()), CoordinateToInt(size.Y())));
}

CustomTexture::CustomTexture(SDL_Renderer* renderer_ptr, SDL_Texture* texture_ptr):m_renderer{renderer_ptr}, m_texture{DuplicateSDLTexture(m_renderer, texture_ptr)},
    m_src_rect{nullptr}, m_dst_rect{nullptr}, m_colour_modulation{255,255,255,255}
{

}

CustomTexture::~CustomTexture() noexcept
{
    /* This class does not own the renderer ptr, so DO NOT DELETE IT */
    ClearSourceRect();
    ClearDestinationRect();
}

CustomTexture::CustomTexture(const CustomTexture& other): m_renderer{other.m_renderer}, m_texture{DuplicateSDLTexture(other.m_renderer, other.m_texture)},
    m_src_rect{other.m_src_rect}, m_dst_rect{other.m_dst_rect}, m_colour_modulation{other.m_colour_modulation}
{

}

CustomTexture::CustomTexture(CustomTexture&& other) noexcept
{
    m_renderer = std::move(other.m_renderer);
    m_texture = std::move(other.m_texture);

    m_src_rect = std::move(other.m_src_rect);
    m_dst_rect = std::move(other.m_dst_rect);

    m_colour_modulation = std::move(other.m_colour_modulation);
}

CustomTexture& CustomTexture::operator=(const CustomTexture& other)
{
    if(this != &other)//not same ref
    {
        CustomTexture tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

CustomTexture& CustomTexture::operator=(CustomTexture&& other) noexcept
{
    this->m_renderer = std::move(other.m_renderer);
    this->m_texture = std::move(other.m_texture);

    this->m_src_rect = std::move(other.m_src_rect);
    this->m_dst_rect = std::move(other.m_dst_rect);
    this->m_colour_modulation = std::move(other.m_colour_modulation);

    return *this;
}

void CustomTexture::SourceRect(SDL_Rect src_rect)
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

void CustomTexture::DestinationRect(SDL_Rect dst_rect)
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

void CustomTexture::ClearSourceRect()
{
    delete(m_src_rect);
    m_src_rect = nullptr;
}

void CustomTexture::ClearDestinationRect()
{
    delete(m_dst_rect);
    m_dst_rect = nullptr;
}

void CustomTexture::TexturePtr(SDL_Texture* texture)
{
    //will delete the previous one on its own
    m_texture.reset(texture);
}

void CustomTexture::Render()
{
    Render(m_src_rect, m_dst_rect);
}

void CustomTexture::Render(SDL_Rect* src_rect, SDL_Rect* dst_rect)
{
    if(m_texture == nullptr)
        return;

    SDL_SetTextureAlphaMod(m_texture.get(), m_colour_modulation.a);
    SDL_SetTextureColorMod(m_texture.get(), m_colour_modulation.r, m_colour_modulation.g, m_colour_modulation.b);
    SDL_RenderCopy(m_renderer, m_texture.get(), src_rect, dst_rect);
    //we reset the alpha and color modulation after rendering as the texture may be shared
    SDL_SetTextureColorMod(m_texture.get(), 255, 255, 255);
    SDL_SetTextureAlphaMod(m_texture.get(), 255);
}

void CustomTexture::RenderEx(SDL_Rect* src_rect, SDL_Rect* dst_rect, double angle, SDL_Point* rotation_pivot, SDL_RendererFlip flip)
{
    if(m_texture.get() == nullptr)
        return;

    // SDL_SetTextureBlendMode(m_texture_ptr, m_blend_mode);
    SDL_SetTextureAlphaMod(m_texture.get(), m_colour_modulation.a);
    SDL_SetTextureColorMod(m_texture.get(), m_colour_modulation.r, m_colour_modulation.g, m_colour_modulation.b);

    SDL_RenderCopyEx(m_renderer, m_texture.get(), src_rect, dst_rect, angle, rotation_pivot, flip);

    //we reset the alpha and color modulation after rendering as the texture may be shared
    SDL_SetTextureColorMod(m_texture.get(), 255, 255, 255);
    SDL_SetTextureAlphaMod(m_texture.get(), 255);
    // SDL_SetTextureBlendMode(m_texture_ptr, SDL_BlendMode::SDL_BLENDMODE_BLEND);
}

void CustomTexture::Resize(int new_w, int new_h, bool scale_content)
{
    //store new texture. unique_ptr will use the deleter to delete the previous one
    ResizeSDLTexture(m_renderer, m_texture, new_w, new_h, scale_content);
}

void CustomTexture::Clear(const SDL_Colour& colour)
{
    ClearSDLTexture(m_renderer, m_texture.get(), colour);
}

void CustomTexture::ColourModulation(const SDL_Colour& colour)
{
    ColourModulation(colour.r, colour.g, colour.b);
}

void CustomTexture::ColourModulation(Uint8 r, Uint8 g, Uint8 b)
{
    m_colour_modulation.r = r;
    m_colour_modulation.g = g;
    m_colour_modulation.b = b;
}

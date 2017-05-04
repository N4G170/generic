#include "texture.hpp"
#include <utility>
#include <iostream>
#include <SDL2/SDL_image.h>

Texture::Texture(const std::string& source_path, SDL_Renderer* renderer_ptr): m_width{0}, m_height{0},
    m_pixel_format{0}, m_texture_access{0}, m_renderer_ptr{renderer_ptr},  m_texture_ptr{nullptr}
{
    SDL_Surface* surface = IMG_Load(source_path.c_str());
    if( !surface )
    {
        std::cout<< "Unable to load image file \""<< source_path <<"\"! SDL Error: "<< SDL_GetError()<<std::endl;

        m_texture_ptr = SDL_CreateTexture(m_renderer_ptr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 0, 0);
    }
    else
    {
        m_texture_ptr = SDL_CreateTextureFromSurface(m_renderer_ptr, surface);
        SDL_FreeSurface(surface);
    }

    //update texture metadata
    SDL_QueryTexture(m_texture_ptr, &m_pixel_format, &m_texture_access, &m_width, &m_height);
}

Texture::Texture(SDL_Texture* texture_ptr, SDL_Renderer* renderer_ptr):  m_width{0}, m_height{0}, m_renderer_ptr{renderer_ptr},  m_texture_ptr{texture_ptr}
{
    SDL_QueryTexture(texture_ptr, &m_pixel_format, &m_texture_access, &m_width, &m_height);
}

// Texture::Texture(SDL_Texture*&& texture_ptr, SDL_Renderer* renderer_ptr): m_width{0}, m_height{0}, m_renderer_ptr{renderer_ptr},  m_texture_ptr{std::move(texture_ptr)}
// {
//
// }

Texture::Texture(SDL_Renderer* renderer_ptr, int width, int height, Uint32 pixel_format, int texture_access): m_width{width},
    m_height{height}, m_pixel_format{pixel_format}, m_texture_access{texture_access}, m_renderer_ptr{renderer_ptr},  m_texture_ptr{nullptr}
{
    m_texture_ptr = SDL_CreateTexture(m_renderer_ptr, m_pixel_format, m_texture_access, m_width, m_height);
}

Texture::~Texture() noexcept
{
    SDL_DestroyTexture(m_texture_ptr);
    m_texture_ptr = nullptr;
    m_renderer_ptr = nullptr;
}

Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);//will call move operator=, the one bellow
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    //we are moving the object to itself
    if(this == &other)
        return *this;

    //delete previous texture, if it exists
    if(this->m_texture_ptr != nullptr)
    {
        SDL_DestroyTexture(m_texture_ptr);
        m_texture_ptr = nullptr;
    }

    this->m_width = std::move(other.m_width);
    this->m_height = std::move(other.m_height);
    this->m_pixel_format = std::move(other.m_pixel_format);
    this->m_texture_access = std::move(other.m_texture_access);

    this->m_renderer_ptr = std::move(other.m_renderer_ptr);
    this->m_texture_ptr = std::move(other.m_texture_ptr);
    this->m_source_path = std::move(other.m_source_path);

    return *this;
}

//Texture Helper Render Functions
void RenderTexture(SDL_Texture* texture, SDL_Renderer* renderer_ptr, SDL_Rect* source_rect, SDL_Rect* destination_rect)
{
    SDL_RenderCopy(renderer_ptr, texture, source_rect, destination_rect);
}

bool RenderOnTexture(SDL_Renderer* renderer_ptr, Texture* source_texture, const Texture* destination_texture, SDL_Rect* source_rect, SDL_Rect* destination_rect)
{
    if(destination_texture->TextureAccess() == SDL_TEXTUREACCESS_TARGET)//ok, can render to texture
    {
        SDL_SetRenderTarget(renderer_ptr, destination_texture->TexturePtr());//set texture as new target

        SDL_RenderCopy(renderer_ptr, source_texture ->TexturePtr(), source_rect, destination_rect);

        SDL_SetRenderTarget(renderer_ptr, nullptr);//reset target to window
        return true;
    }

    return false;
}

void ResetTextureToTransparency(SDL_Renderer* renderer_ptr, SDL_Texture* texture)
{
    SDL_SetRenderTarget(renderer_ptr, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_ptr, 255, 255, 255, 0);//tranparência
    SDL_RenderClear(renderer_ptr);
    SDL_SetRenderTarget(renderer_ptr, nullptr);
}

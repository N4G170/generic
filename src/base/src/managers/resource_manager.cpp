#include "resource_manager.hpp"
#include <utility>
#include "SDL_image.h"

ResourceManager::ResourceManager(SDL_Renderer* renderer_ptr): m_renderer_ptr{renderer_ptr}
{

}

ResourceManager::~ResourceManager() noexcept
{
    m_renderer_ptr = nullptr;
}

ResourceManager::ResourceManager(const ResourceManager& other): m_renderer_ptr{other.m_renderer_ptr}
{

}

ResourceManager::ResourceManager(ResourceManager&& other) noexcept
{
    m_renderer_ptr = std::move(other.m_renderer_ptr);
}

ResourceManager& ResourceManager::operator=(const ResourceManager& other)
{
    if(this != &other)//not same ref
    {
        ResourceManager tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept
{
    this->m_renderer_ptr = std::move(other.m_renderer_ptr);

    return *this;
}

Texture ResourceManager::GetTexture(const std::string& texture_path)
{
    if(m_sdl_textures.find(texture_path) == std::end(m_sdl_textures))//did not find it
    {
        SDL_Surface* image = IMG_Load(texture_path.data());//load new
        if(image)//image loaded
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer_ptr, image);
            if(texture)
            {
                m_sdl_textures.emplace(texture_path, std::unique_ptr<SDL_Texture, SDLDeleters>{texture});
            }
            else
            {
                // LogLine("Failed to create texture from surface. File path:"+texture_path);
                return {};
            }
        }
        else
        {
            // LogLine("Failed to create surface from file. File path:"+texture_path);
            return {};
        }
    }
    return Texture{m_renderer_ptr, m_sdl_textures[texture_path].get(), texture_path};//create new Texture object
}

void ResourceManager::Clear()
{
    m_sdl_textures.clear();
}

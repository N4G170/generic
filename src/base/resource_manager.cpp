#include "resource_manager.hpp"
#include <utility>

ResourceManager::ResourceManager(SDL_Renderer* renderer_ptr): m_renderer_ptr{renderer_ptr}
{

}

ResourceManager::~ResourceManager() noexcept
{
    m_textures.clear();
}

ResourceManager::ResourceManager(ResourceManager&& other) noexcept
{

}

ResourceManager& ResourceManager::operator=(ResourceManager&& other) noexcept
{
    //we are moving the object to itself
    if(this == &other)
        return *this;

    m_renderer_ptr = std::move(other.m_renderer_ptr);
    m_textures = std::move(other.m_textures);

    return *this;
}

void ResourceManager::LoadTexture(const std::string &source_path)
{
    if(m_textures.find(source_path) != m_textures.end())//element exists
        return;

    m_textures.emplace(std::make_pair(source_path, Texture(source_path, m_renderer_ptr)));
}

void ResourceManager::LoadTexture(const std::vector<std::string> &source_paths)
{
    for(const std::string& path : source_paths)
    {
        LoadTexture(path);
    }
}

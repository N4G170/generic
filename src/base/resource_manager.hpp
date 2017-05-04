#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "texture.hpp"//includes SDL2

class ResourceManager
{
    public:
        /* Default constructor */
        explicit ResourceManager(SDL_Renderer* renderer_ptr);
        /* Default destructor */
        virtual ~ResourceManager() noexcept;

        /* Copy constructor */
        ResourceManager(const ResourceManager& other) = delete;
        /* Move constructor */
        ResourceManager(ResourceManager&& other) noexcept;

        /* Copy operator */
        ResourceManager& operator= (const ResourceManager& other) = delete;
        /* Move operator */
        ResourceManager& operator= (ResourceManager&& other) noexcept;

        //textures
        void LoadTexture(const std::string& source_path);
        void LoadTexture(const std::vector<std::string>& source_paths);

        Texture* GetTexture(const std::string& source_path);

    private:
        // vars and stuff
        SDL_Renderer* m_renderer_ptr;
        std::map<std::string, Texture> m_textures;
};

#endif //RESOURCE_MANAGER_HPP

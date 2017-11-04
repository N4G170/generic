#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include "texture.hpp"
#include "SDL.h"
#include <memory>
#include "deleters.hpp"

class ResourceManager
{
    public:
        /* Default constructor */
        explicit ResourceManager(SDL_Renderer* renderer_ptr);
        /* Default destructor */
        virtual ~ResourceManager() noexcept;

        /* Copy constructor */
        ResourceManager(const ResourceManager& other);
        /* Move constructor */
        ResourceManager(ResourceManager&& other) noexcept;

        /* Copy operator */
        ResourceManager& operator= (const ResourceManager& other);
        /* Move operator */
        ResourceManager& operator= (ResourceManager&& other) noexcept;

        Texture GetTexture(const std::string& texture_path);
        // Font* GetFont(const std::string& font_path, int font_size);

        /**
         * \brief Delete all pointers to external resources
         */
        void Clear();
    private:
        // vars and stuff
        /* This class IS NOT THE OWNER OF THS POINTER */
        SDL_Renderer* m_renderer_ptr;

        std::map<std::string, std::unique_ptr<SDL_Texture, SDLDeleters>> m_sdl_textures;
};

#endif //RESOURCE_MANAGER_HPP

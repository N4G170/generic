#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SDL.h"
#include <memory>
#include <string>

#include "deleters.hpp"

class Texture
{
    public:
        /* Base constructor */
        Texture(const std::string& source_path, SDL_Renderer* renderer_ptr);

        Texture(SDL_Texture* texture_ptr, SDL_Renderer* renderer_ptr);

        // Texture(SDL_Texture*&& texture_ptr, SDL_Renderer* renderer_ptr);

        Texture(SDL_Renderer* renderer_ptr, int width, int height, Uint32 pixel_format = SDL_PIXELFORMAT_RGBA8888, int texture_access = SDL_TEXTUREACCESS_STATIC);

        /* Default destructor */
        virtual ~Texture() noexcept;

        /* Copy constructor */
        Texture(const Texture& other) = delete;
        /* Move constructor */
        Texture(Texture&& other) noexcept;

        /* Copy operator */
        Texture& operator= (const Texture& other) = delete;
        /* Move operator */
        Texture& operator= (Texture&& other) noexcept;

        //getters
        int Width() const { return m_width; }
        int Height() const { return m_height; }
        Uint32 PixelFormat() const { return m_pixel_format; }
        int TextureAccess() const { return m_texture_access; }
        std::string SourcePath() const { return m_source_path; }
        SDL_Texture* TexturePtr() const { return m_texture_ptr; }

    private:
        // vars and stuff
        int m_width;
        int m_height;
        Uint32 m_pixel_format;
        int m_texture_access;

        SDL_Renderer* m_renderer_ptr;
        SDL_Texture* m_texture_ptr;
        std::string m_source_path;
};

//Texture Helper Render Functions
void RenderTexture(SDL_Texture* texture, SDL_Renderer* renderer_ptr, SDL_Rect* source_rect = nullptr, SDL_Rect* destination_rect = nullptr);
bool RenderOnTexture(SDL_Renderer* renderer_ptr, Texture* source_texture, const Texture* destination_texture, SDL_Rect* source_rect = nullptr, SDL_Rect* destination_rect = nullptr);
void ResetTextureToTransparency(SDL_Renderer* renderer_ptr, SDL_Texture* texture);

#endif //TEXTURE_HPP

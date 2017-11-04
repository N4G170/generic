#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SDL.h"
#include <memory>
#include <string>

#include "deleters.hpp"

class Texture
{
    public:
        //<f> Constructors & operator=

        /* Default constructor */
        Texture();
        Texture(SDL_Renderer* renderer_ptr, SDL_Texture* texture_ptr, const std::string& image_path);
        /* Default destructor */
        virtual ~Texture() noexcept;

        /* Copy constructor */
        Texture(const Texture& other);
        /* Move constructor */
        Texture(Texture&& other) noexcept;

        /* Copy operator */
        Texture& operator= (const Texture& other);
        /* Move operator */
        Texture& operator= (Texture&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Getters/Setters
        void ColourModulation(const SDL_Colour& colour){ m_colour_modulation = colour; }
        SDL_Colour ColourModulation() const { return m_colour_modulation; }

        Uint8 RedModulation() const { return m_colour_modulation.b; }
        void RedModulation(Uint8 red){ m_colour_modulation.b = red;}

        Uint8 GreenModulation() const { return m_colour_modulation.b; }
        void GreenModulation(Uint8 green){ m_colour_modulation.b = green;}

        Uint8 BlueModulation() const { return m_colour_modulation.b; }
        void BlueModulation(Uint8 blue){ m_colour_modulation.b = blue;}

        Uint8 AlphaModulation() const { return m_colour_modulation.a; }
        void AlphaModulation(Uint8 alpha){ m_colour_modulation.a = alpha;}

        void ChangeTexturePtr(SDL_Texture* new_texture) { m_texture_ptr = new_texture; }

        std::string ImagePath() const { return m_image_path; }

        void BlendMode(SDL_BlendMode mode);
        SDL_BlendMode BlendMode() const;
        //</f>

        void Render(SDL_Rect* src_rect, SDL_Rect* dst_rect);
        /**
         * \brief Render the texture with rotation
         * \n if rotation_pivot is nullptr the used pivot will be the centre of the destination rect.
         * \n rotation_pivot value is local
         */
        void RenderEx(SDL_Rect* src_rect, SDL_Rect* dst_rect, double angle = 0, SDL_Point* rotation_pivot = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        // SDL_Texture* DuplicateTexture();

    private:
        // vars and stuff
        //Texture DOES NOT OWN THIS POINTER
        SDL_Renderer* m_renderer_ptr;
        //Texture DOES NOT OWN THIS POINTER IF m_manage_memory == FALSE
        SDL_Texture* m_texture_ptr;

        SDL_Colour m_colour_modulation;
        SDL_BlendMode m_blend_mode;
        std::string m_image_path;
};

#endif //TEXTURE_HPP

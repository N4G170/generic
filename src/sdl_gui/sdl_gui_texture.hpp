#include <SDL2/SDL.h>

namespace sdl_gui
{

#ifndef SDL_GUI_TEXTURE_HPP
#define SDL_GUI_TEXTURE_HPP

class Texture
{
    public:
        /* Default constructor */
        Texture();
        Texture(SDL_Renderer* renderer_ptr, SDL_Texture* texture_ptr);
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

        /* < Getters/Setters > */
        SDL_Rect* SourceRect() const { return m_src_rect; };
        void SourceRect(SDL_Rect src_rect);
        SDL_Rect* DestinationRect() const { return m_dst_rect; };
        void DestinationRect(SDL_Rect dst_rect);
        void ClearSourceRect();
        void ClearDestinationRect();
        SDL_Colour ColorModulation() const { return m_colour_modulation; };
        void ColorModulation(const SDL_Colour& colour) { m_colour_modulation = colour; };
        /* < /Getters/Setters > */

        void Render();
        void Render(SDL_Rect* src_rect, SDL_Rect* dst_rect);

    private:
        // vars and stuff
        //Texture DOES NOT OWN THIS POINTER
        SDL_Renderer* m_renderer_ptr;
        //Texture DOES NOT OWN THIS POINTER IF m_manage_memory == FALSE
        SDL_Texture* m_texture_ptr;

        SDL_Rect* m_src_rect;
        SDL_Rect* m_dst_rect;
        SDL_Colour m_colour_modulation;
};

#endif //TEXTURE_HPP

}

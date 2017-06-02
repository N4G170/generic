#include <SDL2/SDL.h>
#include "sdl_gui_element.hpp"
#include <string>
#include <memory>

namespace sdl_gui
{

#ifndef SDL_GUI_IMAGE_HPP
#define SDL_GUI_IMAGE_HPP

class Image : public GuiElement
{
    public:
        /* Base constructor */
        Image(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, const std::string& texture_path);
        /* Default destructor */
        virtual ~Image() noexcept;

        /* Copy constructor */
        Image(const Image& other);
        /* Move constructor */
        Image(Image&& other) noexcept;

        /* Copy operator */
        Image& operator= (const Image& other);
        /* Move operator */
        Image& operator= (Image&& other) noexcept;

        /* < Overrides GUIElement > */
        void Render(float delta_time);
        void Render(SDL_Renderer* renderer_ptr, float delta_time);
        void Logic(float fixed_delta_time);
        /* </ Overrides > */


        void SetSourceRect(SDL_Rect src_rect);
        void ClearSourceRect();
        void SetDestinationRect(SDL_Rect dst_rect);
        void ClearDestinationRect();

    private:
        // vars and stuff
        SDL_Texture* m_texture;
        std::unique_ptr<SDL_Rect> m_source_rect;
        bool m_has_destination_rect;
};

#endif //GUI_IMAGE_HPP

}//namespace

#include "SDL.h"
#include "sdl_gui_element.hpp"
#include "sdl_gui_render.hpp"
#include <string>
#include <memory>

namespace sdl_gui
{

#ifndef SDL_GUI_PANEL_HPP
#define SDL_GUI_PANEL_HPP

class Panel : public GuiElement, public IGuiRender
{
    public:
        //<f> Constructors & operator=
        /* Base constructor */
        Panel(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, const std::string& texture_path);
        /* Default destructor */
        virtual ~Panel() noexcept;

        /* Copy constructor */
        Panel(const Panel& other);
        /* Move constructor */
        Panel(Panel&& other) noexcept;

        /* Copy operator */
        Panel& operator= (const Panel& other);
        /* Move operator */
        Panel& operator= (Panel&& other) noexcept;
        //</f>

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
        Texture m_texture;
        std::unique_ptr<SDL_Rect> m_source_rect;
};

#endif //SDL_GUI_PANEL_HPP

}//namespace

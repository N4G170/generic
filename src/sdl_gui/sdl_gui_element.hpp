#include <SDL2/SDL.h>
#include <list>
#include <functional>
#include "sdl_gui_transform.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_resource_manager.hpp"
#include "font.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_ELEMENT_HPP
#define SDL_GUI_ELEMENT_HPP

class GuiElement
{
    public:
        GuiElement(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position local_position, Dimensions dimensions);
        /* Default constructor */
        GuiElement();
        /* Default destructor */
        virtual ~GuiElement() noexcept;

        /* Copy constructor */
        GuiElement(const GuiElement& other);
        /* Move constructor */
        GuiElement(GuiElement&& other) noexcept;

        /* < Pure Virtual Funtions > */
        virtual void Logic(float fixed_delta_time) = 0;
        virtual void Render(float delta_time) = 0;
        virtual void Render(SDL_Renderer* renderer_ptr, float delta_time) = 0;
        /* </ Pure Virtual Funtions > */

        //<f> Getters/Setters
        GuiTransform* TransformPtr() { return &m_transform; }
        void ZIndex(int z_index){ m_z_index = z_index; }
        int ZIndex() const { return m_z_index; }
        void RenderBoundsBorder(bool render_bounds_border){ m_render_bounds_border = render_bounds_border; }
        bool RenderBoundsBorder() const { return m_render_bounds_border; }
        void BorderColour(const SDL_Colour& border_colour){ m_border_colour = border_colour; }
        SDL_Colour BorderColour() const { return m_border_colour; }
        //</f>

    protected:
        // vars and stuff
        GuiTransform m_transform;

        // AnchorType m_anchor_type;
        int m_z_index;
        bool m_render_bounds_border;
        SDL_Colour m_border_colour;

        ResourceManager* m_resource_manager_ptr;
        SDL_Renderer* m_renderer_ptr;

        virtual void RenderBorder();
};

#endif //GUI_ELEMENT_HPP

}//namespace

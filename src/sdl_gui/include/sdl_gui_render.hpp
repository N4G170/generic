#include <utility>
#include "SDL.h"
#include "sdl_gui_resource_manager.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_RENDER_HPP
#define SDL_GUI_RENDER_HPP

/**
 * Interface used by elements that want to render to the screen
 */
class IGuiRender
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        IGuiRender();

        explicit IGuiRender(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr);
        /* Default destructor */
        virtual ~IGuiRender() noexcept;

        /* Copy constructor */
        IGuiRender(const IGuiRender& other);
        /* Move constructor */
        IGuiRender(IGuiRender&& other) noexcept;

        /* Copy operator */
        IGuiRender& operator= (const IGuiRender& other);
        /* Move operator */
        IGuiRender& operator= (IGuiRender&& other) noexcept;
        //</f>

        //<f> Virtual Methods
        virtual void Render(float delta_time) = 0;
        virtual void RenderBorder(float delta_time);
        //</f>

        //<f> Getters/Setters
        void ZIndex(int z_index){ m_zindex = z_index; }
        int ZIndex() const { return m_zindex; }

        void RenderBorder(bool render_border){ m_render_border = render_border; }
        bool RenderBorder() const { return m_render_border; }

        void BorderColour(const SDL_Colour& border_colour){ m_border_colour = border_colour; }
        SDL_Colour BorderColour() const { return m_border_colour; }
        //</f>

    protected:
        /**
         * Raw pointer to the main renderer (this class DOES NOT own it)
         */
        SDL_Renderer* m_renderer_ptr;

        /**
         * Raw pointer to the resource manager that allow the load of images and fonts
         */
        ResourceManager* m_resource_manager_ptr;

        /**
         * True - render element
         * False - Do not render
         */
        bool m_render;

        /**
         * Index for the render order. The bigger the further back the element is
         */
        int m_zindex;

        /**
         * True - Render a border around the bounds of the element
         */
        bool m_render_border;

        /**
         * Colour of the border to be drawn (default {0,0,0,255})
         */
        SDL_Colour m_border_colour;

        /**
         * SDL_Rect with the coordinates and dimensions of the border
         */
        SDL_Rect m_border_rect;
};

#endif //SDL_GUI_RENDER_HPP
}

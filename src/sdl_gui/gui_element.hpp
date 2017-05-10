#include <SDL2/SDL.h>
#include <list>
#include "gui_transform.hpp"

namespace sdl_gui
{

#ifndef GUI_ELEMENT_HPP
#define GUI_ELEMENT_HPP

enum AnchorType
{
    TOP_LEFT,
    TOP_CENTRE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTRE,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTRE,
    BOTTOM_RIGHT
};

class GuiElement
{
    public:
        GuiElement(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
        /* Default constructor */
        GuiElement();
        /* Default destructor */
        virtual ~GuiElement() noexcept;

        /* Copy constructor */
        GuiElement(const GuiElement& other);
        /* Move constructor */
        GuiElement(GuiElement&& other) noexcept;

        /* Copy operator */
        GuiElement& operator= (const GuiElement& other);
        /* Move operator */
        GuiElement& operator= (GuiElement&& other) noexcept;

        /* < Pure Virtual Funtions > */
        virtual void Logic() = 0;
        virtual void Render() = 0;
        virtual void Render(SDL_Renderer* renderer_ptr) = 0;
        /* </ Pure Virtual Funtions > */

        /* < Getters / Setters > */
        void ZIndex(int z_index){ m_z_index = z_index; }
        int ZIndex() const { return m_z_index; }
        /* </ Getters / Setters > */

    protected:
        // vars and stuff
        GuiTransform m_transform;
        Position m_position;
        Dimensions m_dimensions;

        // AnchorType m_anchor_type;
        int m_z_index;

        SDL_Renderer* m_renderer_ptr;

        GuiElement* m_parent;
        // std::list<GuiElement*> m_children;
};

#endif //GUI_ELEMENT_HPP

}//namespace

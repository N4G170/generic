#include <SDL2/SDL.h>
#include <list>
#include "gui_collider.hpp"

namespace sdl_gui
{

#ifndef GUI_INTERACTION_HPP
#define GUI_INTERACTION_HPP

class GuiInteraction
{
    public:
        /* Default constructor */
        GuiInteraction();
        /* Default destructor */
        virtual ~GuiInteraction() noexcept;

        /* Copy constructor */
        GuiInteraction(const GuiInteraction& other);
        /* Move constructor */
        GuiInteraction(GuiInteraction&& other) noexcept;

        /* Copy operator */
        GuiInteraction& operator= (const GuiInteraction& other);
        /* Move operator */
        GuiInteraction& operator= (GuiInteraction&& other) noexcept;

        virtual void Input(const SDL_Event& event) = 0;

        /* Add Box collider */
        void AddGuiCollider(const SDL_Rect& collider_dimensions);
        /* Add Circle collider */
        void AddGuiCollider(int centre_x, int centre_y, int circle_radius);

        virtual bool MouseInsideCollider(int mouse_x, int mouse_y);

    protected:
        // vars and stuff
        std::list<GuiCollider> m_colliders;
};

#endif //GUI_INTERACTION_HPP
}//namespace

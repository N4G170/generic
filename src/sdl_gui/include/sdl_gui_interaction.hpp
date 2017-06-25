#include "SDL.h"
#include <list>
#include <map>
#include <functional>
#include "sdl_gui_collider.hpp"
#include "sdl_gui_enums.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_INTERACTION_HPP
#define SDL_GUI_INTERACTION_HPP

class IGuiInteraction
{
    public:
        /* Default constructor */
        IGuiInteraction();

        explicit IGuiInteraction(bool active);
        /* Default destructor */
        virtual ~IGuiInteraction() noexcept;

        /* Copy constructor */
        IGuiInteraction(const IGuiInteraction& other);
        /* Move constructor */
        IGuiInteraction(IGuiInteraction&& other) noexcept;

        /* Copy operator */
        IGuiInteraction& operator= (const IGuiInteraction& other);
        /* Move operator */
        IGuiInteraction& operator= (IGuiInteraction&& other) noexcept;

        virtual void Input(const SDL_Event& event);
        virtual void ClearInput();
        virtual void CallBacksLogic(float delta_time);

        /* Add Box collider */
        void AddGuiCollider(const Position& position, const Dimensions& dimensions, GuiTransform* owner_transform);
        /* Add Circle collider */
        void AddGuiCollider(const Position& position, int circle_radius, GuiTransform* owner_transform);

        virtual bool MouseInsideCollider(int mouse_x, int mouse_y);

        /* < Getters/Setters > */
        void Active(bool active) { m_active = active; }
        bool Active(bool active) const { return m_active; }

        std::function<void()>* MouseCallback(MouseCallbackType type) { return &m_mouse_callbacks[type]; }
        void MouseCallback(MouseCallbackType type, const std::function<void()>& callback) { m_mouse_callbacks[type] = callback; }

    protected:
        // vars and stuff
        std::list<Collider> m_colliders;
        bool m_active;
        bool m_under_focus;
        //mouse flags
        int m_mouse_flags;
        float m_valid_click_timer;

        /* < CallBacks > */
        std::map<MouseCallbackType, std::function<void()>> m_mouse_callbacks;
        /* </ CallBacks > */
};

#endif //GUI_INTERACTION_HPP
}//namespace

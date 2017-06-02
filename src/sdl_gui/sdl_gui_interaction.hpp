#include <SDL2/SDL.h>
#include <list>
#include <vector>
#include <functional>
#include "sdl_gui_collider.hpp"
#include "sdl_gui_enums.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_INTERACTION_HPP
#define SDL_GUI_INTERACTION_HPP

class GuiInteraction
{
    public:
        /* Default constructor */
        GuiInteraction();

        explicit GuiInteraction(bool active);
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

        /**
         * \brief Called every logic cycle
         */
        std::vector<std::function<void()>>* MouseHoverCallbacks(){ return &m_mouse_down_callbacks; }
        /**
         * \brief Called when mouse left button goes down
         */
        std::vector<std::function<void()>>* MouseDownCallbacks(){ return &m_mouse_click_callbacks; }
        /**
         * \brief Called when a we hold the button down and are hover the detection area
         */
        std::vector<std::function<void()>>* MouseHoldCallbacks(){ return &m_mouse_up_callbacks; }
        /**
         * \brief Called when a valid click is detected
         */
        std::vector<std::function<void()>>* MouseClickCallbacks(){ return &m_mouse_up_callbacks; }
        /**
         * \brief Called when the mouse left button goes down
         */
        std::vector<std::function<void()>>* MouseUpCallbacks(){ return &m_mouse_down_callbacks; }
        /**
         * \brief Called when the mouse enters the detection area of the element
         */
        std::vector<std::function<void()>>* MouseEnterCallbacks(){ return &m_mouse_click_callbacks; }
        /**
         * \brief Called when the mouse exits the detection area of the element
         */
        std::vector<std::function<void()>>* MouseExitCallbacks(){ return &m_mouse_up_callbacks; }
        /* </ Getters/Setters > */

    protected:
        // vars and stuff
        std::list<Collider> m_colliders;
        bool m_active;
        //mouse flags
        int m_mouse_flags;
        float m_valid_click_timer;

        /* < CallBacks > */
        std::vector<std::function<void()>> m_mouse_hover_callbacks;
        std::vector<std::function<void()>> m_mouse_down_callbacks;
        std::vector<std::function<void()>> m_mouse_hold_callbacks;
        std::vector<std::function<void()>> m_mouse_click_callbacks;
        std::vector<std::function<void()>> m_mouse_up_callbacks;
        std::vector<std::function<void()>> m_mouse_enter_callbacks;
        std::vector<std::function<void()>> m_mouse_exit_callbacks;
        /* </ CallBacks > */
};

#endif //GUI_INTERACTION_HPP
}//namespace

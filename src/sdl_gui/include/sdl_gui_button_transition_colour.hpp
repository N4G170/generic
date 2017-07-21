#include "sdl_gui_button_transition.hpp"
#include <unordered_map>
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_resource_manager.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_BUTTON_TRANSITION_COLOUR_HPP
#define SDL_GUI_BUTTON_TRANSITION_COLOUR_HPP

class ButtonTransitionColour : public ButtonTransition
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit ButtonTransitionColour(ResourceManager* resource_manager_ptr);
        /** brief Default destructor */
        virtual ~ButtonTransitionColour() noexcept;

        /** brief Copy constructor */
        ButtonTransitionColour(const ButtonTransitionColour& other);
        /** brief Move constructor */
        ButtonTransitionColour(ButtonTransitionColour&& other) noexcept;

        /** brief Copy operator */
        ButtonTransitionColour& operator= (const ButtonTransitionColour& other);
        /** brief Move operator */
        ButtonTransitionColour& operator= (ButtonTransitionColour&& other) noexcept;
        //</f>

        //<f> Virtual Methods
        virtual void Render(const SDL_Rect& dst);
        virtual void ChangeState(ButtonState state);
        //</f>

        //<f> Getters/Setters
        /**
         * \brief Set the colour to be applied to on a specific button state
         */
        void SetStateColour(ButtonState state, const SDL_Colour& colour);
        /**
         * \brief Set the colour to be applied to on a each of the button state
         */
        void SetStateColour(const SDL_Colour& inactive, const SDL_Colour& active, const SDL_Colour& over, const SDL_Colour& pressed);
        //</f>

    protected:
        // vars and stuff
        Texture m_texture;
        SDL_Colour m_current_colour;
        std::unordered_map<ButtonState, SDL_Colour> m_state_colours;

    private:
};

#endif //SDL_GUI_BUTTON_TRANSITION_COLOUR_HPP

}//namespace

#include "sdl_gui_element.hpp"
#include "sdl_gui_image.hpp"
#include "sdl_gui_mouse_interaction.hpp"
#include <memory>
#include <unordered_map>

namespace sdl_gui
{

#ifndef SDL_GUI_BASE_BUTTON_HPP
#define SDL_GUI_BASE_BUTTON_HPP

struct ButtonStateTransition
{
    /**
     * Source area of the image to be used as this state transition
    */
    std::unique_ptr<SDL_Rect> source_rect_ptr;
    /**
     * \brief Color to be applied on the texture (will be reset after rendering)
     */
    SDL_Colour colour;
};

class BaseButton : public GuiElement
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        BaseButton(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
        /* Default destructor */
        virtual ~BaseButton() noexcept;

        /* Copy constructor */
        BaseButton(const BaseButton& other);
        /* Move constructor */
        BaseButton(BaseButton&& other) noexcept;

        /* Copy operator */
        BaseButton& operator= (const BaseButton& other);
        /* Move operator */
        BaseButton& operator= (BaseButton&& other) noexcept;
        //</f>

        //<f> Overrides GUIElement
        virtual void Input(const SDL_Event& event);
        virtual void ClearInput();

        // virtual void FixedLogic(float fixed_delta_time);
        virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
        //</f>

        //<f> Virtual Methods
        /**
         * \brief Set the colour to be applied to on a specific button state
         */
        virtual void SetStateColour(ButtonState button_state, const SDL_Colour& colour);
        /**
         * \brief Set the colour to be applied to on a each of the button state
         */
        virtual void SetStateColours(const SDL_Colour& inactive, const SDL_Colour& active, const SDL_Colour& over, const SDL_Colour& pressed);
        /**
         * \brief Set the source area of the image to be rendered on a specific button state
         */
        virtual void SetStateTextureSrcRect(ButtonState button_state, const SDL_Rect& rect);
        /**
         * \brief Set the source area of the image to be rendered on each of the button state
         */
        virtual void SetStateTextureSrcRect(const SDL_Rect& inactive, const SDL_Rect& active, const SDL_Rect& over, const SDL_Rect& pressed);
        //</f>

        //<f> Getters/Setters
        MouseInteraction* MouseInteractionPtr() { return &m_mouse_interaction; }
        //</f>

    protected:
        // vars and stuff
        // std::map<ButtonState, Texture> m_status_texture;
        std::unordered_map<ButtonState, ButtonStateTransition> m_state_transitions;

        // Texture m_current_texture;
        Texture m_box_texture;
        // Image m_box_texture;

        //interaction
        MouseInteraction m_mouse_interaction;
        SDL_Rect* m_current_source_rect;

        // std::function<void()> TransitionLogic;
        // void ColourTransitionLogic();
        // void TextureTransitionLogic();
        void ButtonTransitionCallback(const ButtonStateTransition& transition);
};

#endif //SDL_GUI_BASE_BUTTON_HPP

}

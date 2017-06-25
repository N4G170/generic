#include "sdl_gui_element.hpp"
#include "sdl_gui_interaction.hpp"
#include "sdl_gui_render.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_BASE_BUTTON_HPP
#define SDL_GUI_BASE_BUTTON_HPP

class BaseButton : public GuiElement, public IGuiRender, public IGuiInteraction
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        BaseButton(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions);
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

        //<f> Overrides IGuiInteraction
        virtual void Input(const SDL_Event& event);
        //</f>

        //<f> Overrides GUIElement
        virtual void Logic(float delta_time);
        //</f>

        //<f> Overrides IGuiRender
        virtual void Render(float delta_time);
        //</f>

        //<f> Virtual Methods
        virtual void SetStateColour(ButtonState button_state, SDL_Colour colour);
        virtual void SetStateColours(SDL_Colour inactive, SDL_Colour active, SDL_Colour hover, SDL_Colour down);
        // virtual void SetStateTexture(ButtonState button_state, Texture texture);
        // virtual void SetStateTexture(Texture inactive, Texture active, Texture hover, Texture down);
        //</f>

        //<f> Getters/Setters
        void TransitionType(ButtonTransitionType type);
        ButtonTransitionType TransitionType();
        //</f>

        void BoxTextureColourModulation(const SDL_Colour& colour);
    protected:
        // vars and stuff
        // std::map<ButtonState, Texture> m_status_texture;
        std::map<ButtonState, SDL_Colour> m_status_colours;

        ButtonTransitionType m_transition_type;
        // Texture m_current_texture;
        Texture m_box_texture;

        // std::function<void()> TransitionLogic;
        // void ColourTransitionLogic();
        // void TextureTransitionLogic();
};

#endif //SDL_GUI_BASE_BUTTON_HPP

}

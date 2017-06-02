#include "sdl_gui_element.hpp"
#include "sdl_gui_interaction.hpp"
#include "sdl_gui_label.hpp"
#include "sdl_gui_image.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"
#include <map>
#include <memory>

namespace sdl_gui
{

#ifndef SDL_GUI_BUTTON_HPP
#define SDL_GUI_BUTTON_HPP

class Button : public GuiElement, public GuiInteraction
{
    public:

        /* Default constructor */
        Button(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
        /* Default destructor */
        virtual ~Button() noexcept;

        /* Copy constructor */
        Button(const Button& other);
        /* Move constructor */
        Button(Button&& other) noexcept;

        /* Copy operator */
        Button& operator= (const Button& other);
        /* Move operator */
        Button& operator= (Button&& other) noexcept;

        /* < Overrides GUIElement > */
        virtual void Logic(float fixed_delta_time);
        virtual void Render(float delta_time);
        virtual void Render(SDL_Renderer* renderer, float delta_time);
        /* </ Overrides > */

        /* < Overrides GuiInteraction > */
        virtual void Input(const SDL_Event& event);
        /* </ Overrides > */

        /* < Getters/Setters > */
        void TransitionType(ButtonTransitionType type);
        ButtonTransitionType TransitionType();
        /* </ Getters/Setters > */

        /* < Virtual Methods > */
        virtual void CreateLabel(const std::string& text, const std::string& font_path, int font_size, const SDL_Colour& text_colour, Position local_position);
        virtual void SetStateColour(ButtonState button_state, SDL_Colour colour);
        virtual void SetStateColours(SDL_Colour inactive, SDL_Colour active, SDL_Colour hover, SDL_Colour down);
        virtual void SetStateTexture(ButtonState button_state, Texture texture);
        virtual void SetStateTexture(Texture inactive, Texture active, Texture hover, Texture down);
        /* </ Virtual Methods > */

    protected:
        // vars and stuff
        std::unique_ptr<Label> m_label_ptr;
        std::map<ButtonState, Texture> m_status_texture;
        std::map<ButtonState, SDL_Colour> m_status_colours;

        ButtonTransitionType m_transition_type;
        Texture m_current_texture;
        Texture m_base_colour_texture;

        std::function<void()> TransitionLogic;
        void ColourTransitionLogic();
        void TextureTransitionLogic();
};

#endif //SDL_GUI_BUTTON_HPP

}//namespace

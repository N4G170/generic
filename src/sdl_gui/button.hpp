#include "gui_element.hpp"
#include "gui_interaction.hpp"
#include "label.hpp"
#include "gui_image.hpp"
#include <map>

namespace sdl_gui
{

#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button : public GuiElement, public GuiInteraction
{
    public:
        /* Default constructor */
        Button(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
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
        void Render();
        void Render(SDL_Renderer* renderer);
        void Logic();
        /* </ Overrides > */

        /* < Overrides GuiInteraction > */
        void Input(const SDL_Event& event);
        /* </ Overrides > */

        void CreateLabel(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& text, const SDL_Colour& text_colour, Position, Dimensions);

        enum ButtonStatus
        {
            INACTIVE,
            ACTIVE,
            HOVER,
            DOWN
        };

        enum TransitionType
        {
            COLOUR,
            TEXTURE
        };

    private:
        // vars and stuff
        Label* m_label_ptr;
        GuiImage* m_image;

        TransitionType m_transition_type;

        //flags
        bool m_mouse_enter;
        bool m_mouse_exit;
        bool m_mouse_hover;
        bool m_mouse_down;

};

#endif //BUTTON_HPP

}//namespace

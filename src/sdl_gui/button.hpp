#include "gui_element.hpp"
#include "gui_interaction.hpp"
#include "label.hpp"
#include "gui_image.hpp"
#include <map>
#include <memory>

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

        enum MouseFlags
        {
            NONE = 0,
            MOUSE_ENTER = 1,
            MOUSE_EXIT = 2,
            MOUSE_HOVER = 4,
            MOUSE_UP = 8,
            MOUSE_DOWN = 16,
        };

    private:
        // vars and stuff
        std::unique_ptr<Label> m_label;
        std::map<ButtonStatus, std::unique_ptr<GuiImage>> m_status_images;
        std::map<ButtonStatus, SDL_Colour> m_status_colours;

        TransitionType m_transition_type;
        GuiImage* m_current_image;
        SDL_Colour m_current_colour;

        //mouse flags
        int m_mouse_flags;
        bool m_allow_click;
};

#endif //BUTTON_HPP

}//namespace

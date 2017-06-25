#include "sdl_gui_base_button.hpp"
#include "sdl_gui_label.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"
#include <map>
#include <memory>

namespace sdl_gui
{

#ifndef SDL_GUI_BUTTON_HPP
#define SDL_GUI_BUTTON_HPP

class Button : public BaseButton
{
    public:

        /* Default constructor */
        Button(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions);
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

        //<f> Overrides IGuiInteraction
        virtual void Input(const SDL_Event& event);
        //</f>

        //<f> Overrides GUIElement
        virtual void Logic(float fixed_delta_time);
        //</f>

        //<f> Overrides IGuiRender
        virtual void Render(float delta_time);
        //</f>

        //<f>  Virtual Methods
        virtual void CreateLabel(const std::string& text, const std::string& font_path, int font_size, const SDL_Colour& text_colour, Position local_position);
        //</f>

    protected:
        // vars and stuff
        std::unique_ptr<Label> m_label_ptr;
};

#endif //SDL_GUI_BUTTON_HPP

}//namespace

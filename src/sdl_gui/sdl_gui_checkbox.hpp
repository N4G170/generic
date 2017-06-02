#include "sdl_gui_element.hpp"
#include "sdl_gui_interaction.hpp"
#include "sdl_gui_texture.hpp"

namespace sdl_gui
{
#ifndef SDL_GUI_CHECKBOX_HPP
#define SDL_GUI_CHECKBOX_HPP

class CheckBox: public GuiElement, public GuiInteraction
{
    public:
        /* Default constructor */
        CheckBox(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
        /* Default destructor */
        virtual ~CheckBox() noexcept;

        /* Copy constructor */
        CheckBox(const CheckBox& other);
        /* Move constructor */
        CheckBox(CheckBox&& other) noexcept;

        /* Copy operator */
        CheckBox& operator= (const CheckBox& other);
        /* Move operator */
        CheckBox& operator= (CheckBox&& other) noexcept;

        // <f> Overrides GUIElement
        virtual void Logic(float fixed_delta_time);
        virtual void Render(float delta_time);
        virtual void Render(SDL_Renderer* renderer, float delta_time);
        // </f>

        // <f> Overrides GuiInteraction
        virtual void Input(const SDL_Event& event);
        //</f>

        //<f> Getters/Setters
        bool IsChecked() const { return m_is_checked; }
        void IsChecked(bool is_checked) { m_is_checked = is_checked; }
        //</f>

    private:
        // vars and stuff
        bool m_is_checked;
        Texture m_box_texture;
        Texture m_check_mark_texture;

        std::map<ButtonState, SDL_Colour> m_status_colours;
};

#endif //SDL_GUI_CHECKBOX_HPP
}//namespace

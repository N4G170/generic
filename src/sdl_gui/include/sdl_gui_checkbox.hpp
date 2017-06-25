#include "sdl_gui_base_button.hpp"
#include "sdl_gui_texture.hpp"
#include <functional>

namespace sdl_gui
{
#ifndef SDL_GUI_CHECKBOX_HPP
#define SDL_GUI_CHECKBOX_HPP

class CheckBox: public BaseButton
{
    public:
        /* Default constructor */
        CheckBox(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions, int value);
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

        //<f> Overrides IGuiInteraction
        virtual void Input(const SDL_Event& event);
        //</f>

        //<f> Overrides GUIElement
        // virtual void Logic(float fixed_delta_time);
        //</f>

        //<f> Overrides IGuiInteraction
        virtual void Render(float delta_time);
        //</f>

        //<f> Getters/Setters
        bool IsChecked() const { return m_is_checked; }
        void IsChecked(bool is_checked) { m_is_checked = is_checked; }
        int Value() const { return m_value; }
        void Value(int new_value) { m_value = new_value; }
        //</f>

        //<f> Callbacks
        std::function<void(CheckBox*)> ValueChanged;

        void MouseClick();
        //</f>
    private:
        // vars and stuff
        bool m_is_checked;
        Texture m_check_mark_texture;

        std::map<ButtonState, SDL_Colour> m_status_colours;

        int m_value;
};

#endif //SDL_GUI_CHECKBOX_HPP
}//namespace

#include "sdl_gui_element.hpp"
#include "sdl_gui_interaction.hpp"
#include "sdl_gui_render.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_base_button.hpp"
#include "sdl_gui_progress_bar.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_SLIDER_HPP
#define SDL_GUI_SLIDER_HPP

class Slider : public ProgressBar, public IGuiInteraction
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        Slider(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions);
        /* Default destructor */
        virtual ~Slider() noexcept;

        /* Copy constructor */
        Slider(const Slider& other);
        /* Move constructor */
        Slider(Slider&& other) noexcept;

        /* Copy operator */
        Slider& operator= (const Slider& other);
        /* Move operator */
        Slider& operator= (Slider&& other) noexcept;
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

        //</f>

        //<f> Getters/Setters

        //</f>

    protected:
        // vars and stuff
        float m_value_change_factor;

        std::unique_ptr<BaseButton> m_head_button;
        std::unique_ptr<BaseButton> m_increase_button;
        std::unique_ptr<BaseButton> m_decrease_button;

        void IncreaseValue(){Value(Value() + m_value_change_factor);};
        void DecreaseValue(){Value(Value() - m_value_change_factor);};
};

#endif //SDL_GUI_SLIDER_HPP

}//namespace

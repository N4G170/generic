#include "sdl_gui_element.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_base_button.hpp"
#include "sdl_gui_progress_bar.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_SLIDER_HPP
#define SDL_GUI_SLIDER_HPP

class Slider : public ProgressBar
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        Slider(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
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

        //<f> Overrides GuiElement
        virtual void Input(const SDL_Event& event);

        // virtual void FixedLogic(float fixed_delta_time);
        virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
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

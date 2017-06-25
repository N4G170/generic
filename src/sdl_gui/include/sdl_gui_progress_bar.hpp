#include "sdl_gui_element.hpp"
#include "sdl_gui_render.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_PROGRESS_BAR_HPP
#define SDL_GUI_PROGRESS_BAR_HPP

class ProgressBar : public GuiElement, public IGuiRender
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        ProgressBar(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions);
        /* Default destructor */
        virtual ~ProgressBar() noexcept;

        /* Copy constructor */
        ProgressBar(const ProgressBar& other);
        /* Move constructor */
        ProgressBar(ProgressBar&& other) noexcept;

        /* Copy operator */
        ProgressBar& operator= (const ProgressBar& other);
        /* Move operator */
        ProgressBar& operator= (ProgressBar&& other) noexcept;
        //</f>

        //<f> Overrides IGuiRender
        virtual void Render(float delta_time);
        //</f>

        //<f> Virtual Methods

        //</f>

        //<f> Getters/Setters
        ProgressBarDirection BarDirection() const { return m_bar_direction; }
        void BarDirection(ProgressBarDirection bar_direction) { m_bar_direction = bar_direction; }

        float Value() const { return m_value; }
        /**
         * Set the current value for the ProgressBar. If the value > max or value < min, value will be set to the right limit
         */
        void Value(float new_value)
        {
            if(new_value > m_max_value) m_value = m_max_value;
            else if(new_value < m_min_value) m_value = m_min_value;
            else m_value = new_value;
        }

        float MaxValue() const { return m_max_value; }
        float MinValue() const { return m_min_value; }
        //</f>

    protected:
        // vars and stuff
        Texture m_bg_texture;
        Texture m_bar_texture;

        ProgressBarDirection m_bar_direction;

        float m_min_value;
        float m_max_value;
        float m_value;

        void RenderLeft();
        void RenderRight();
        void RenderUp();
        void RenderDown();
};

#endif //SDL_GUI_PROGRESS_BAR_HPP

}//namespace

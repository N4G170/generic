#include "sdl_gui_slider.hpp"
#include <utility>
#include <cmath>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{


//<f> Constructors & operator=
Slider::Slider(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions):
    ProgressBar{renderer_ptr, resource_manager_ptr, position, dimensions}
{
    m_increase_button.reset(new BaseButton{renderer_ptr, resource_manager_ptr, position, {25,dimensions.h}});
    m_increase_button->TransformPtr()->Parent(&m_transform);
    m_increase_button->TransformPtr()->LocalPosition({dimensions.w, 0});

    m_decrease_button.reset(new BaseButton{renderer_ptr, resource_manager_ptr, position, {25,dimensions.h}});
    m_decrease_button->TransformPtr()->Parent(&m_transform);
    m_decrease_button->TransformPtr()->LocalPosition({-25, 0});

    m_head_button.reset(new BaseButton{renderer_ptr, resource_manager_ptr, position, {20,dimensions.h}});
    m_head_button->TransformPtr()->Parent(&m_transform);
    m_head_button->TransformPtr()->LocalPosition({dimensions.w/2-10,0});

    m_value_change_factor = 1;

    m_decrease_button->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Slider::DecreaseValue, this));
    // m_decrease_button->MouseCallback(sdl_gui::MouseCallbackType::HOLD, std::bind(&Slider::DecreaseValue, this));
    m_increase_button->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Slider::IncreaseValue, this));
    // m_increase_button->MouseCallback(sdl_gui::MouseCallbackType::HOLD, std::bind(&Slider::IncreaseValue, this));
}

Slider::~Slider() noexcept
{

}

Slider::Slider(const Slider& other): ProgressBar{other}
{

}

Slider::Slider(Slider&& other) noexcept: ProgressBar{other}
{

}

Slider& Slider::operator=(const Slider& other)
{
    if(this != &other)//not same ref
    {
        Slider tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Slider& Slider::operator=(Slider&& other) noexcept
{
    return *this;
}
//</f>

//<f> Overrides GuiInteraction
void Slider::Input(const SDL_Event& event)
{
    if( !m_active )
    return;

    m_decrease_button->Input(event);
    m_increase_button->Input(event);
}
//</f>

//<f> Overrides GUIElement
void Slider::Logic(float delta_time)
{
    Position head_position {m_head_button->TransformPtr()->LocalPosition()};

    head_position.x = std::fmin(m_transform.Size().w * m_value/m_max_value, m_transform.Size().w);

    m_head_button->TransformPtr()->LocalPosition(head_position);

    m_decrease_button->Logic(delta_time);
    m_increase_button->Logic(delta_time);
}

//</f>

//<f> Overrides IGuiRender
void Slider::Render(float delta_time)
{

    ProgressBar::Render(delta_time);

    m_increase_button->Render(delta_time);
    m_decrease_button->Render(delta_time);
    m_head_button->Render(delta_time);

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

}//namespace

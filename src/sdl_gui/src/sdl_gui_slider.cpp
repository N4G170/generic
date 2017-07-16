#include "sdl_gui_slider.hpp"
#include <utility>
#include <cmath>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

//<f> Constructors & operator=
Slider::Slider(GuiMainPointers main_pointers, const Position& position, const Dimensions& size):
    ProgressBar{main_pointers, position, size}
{
    m_increase_button.reset(new BaseButton{main_pointers, position, {25,size.h}});
    m_increase_button->Parent(this);
    m_increase_button->TransformPtr()->LocalPosition({size.w, 0});

    m_decrease_button.reset(new BaseButton{main_pointers, position, {25,size.h}});
    m_decrease_button->Parent(this);
    m_decrease_button->TransformPtr()->LocalPosition({-25, 0});

    m_head_button.reset(new BaseButton{main_pointers, position, {20,size.h}});
    m_head_button->Parent(this);
    m_head_button->TransformPtr()->LocalPosition({size.w/2-10,0});

    m_value_change_factor = 1;

    // m_decrease_button->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Slider::DecreaseValue, this));
    // m_decrease_button->MouseCallback(sdl_gui::MouseCallbackType::HOLD, std::bind(&Slider::DecreaseValue, this));
    // m_increase_button->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Slider::IncreaseValue, this));
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

//<f> Overrides GUIElement
void Slider::Input(const SDL_Event& event)
{
    if( !m_active )
    return;

    m_decrease_button->Input(event);
    m_increase_button->Input(event);
}

void Slider::Logic(float delta_time)
{
    Position head_position {m_head_button->TransformPtr()->LocalPosition()};

    head_position.x = std::fmin(Size().w * m_value/m_max_value, Size().w);

    m_head_button->TransformPtr()->LocalPosition(head_position);

    m_decrease_button->Logic(delta_time);
    m_increase_button->Logic(delta_time);
}

void Slider::Render(float delta_time)
{
    Render(delta_time, m_main_pointers.main_camera_ptr);
}

void Slider::Render(float delta_time, Camera* camera)
{
    if(!m_render)
    return;

    //Cannot call -> "ProgressBar::Render(delta_time);"
    //As it starts an infinite loop of calls because ProgressBar::Render(delta_time) will call (the child)Slider::Render(float delta_time, Camera* camera)
    //and it will call ProgressBar::Render(delta_time) again. You get the point
    ProgressBar::Render(delta_time, camera);

    SDL_Rect dst{RenderRect()};

    //apply camera position
    if(!m_transform.ParentViewport())//if inside viewport we cant add camera position
    {
        dst.x += camera->CameraPosition().x;
        dst.y += camera->CameraPosition().y;
    }

    if(camera->RectInsideCamera(dst))
    {
        m_increase_button->Render(delta_time);
        m_decrease_button->Render(delta_time);
        m_head_button->Render(delta_time);
    }

}
//</f>

}//namespace

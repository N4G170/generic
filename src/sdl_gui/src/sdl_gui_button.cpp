#include "sdl_gui_button.hpp"
#include "sdl_gui_constants.hpp"
#include <utility>
#include <string>
#include "SDL_image.h"
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

Button::Button(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions):
    BaseButton{renderer_ptr, resource_manager_ptr, position, dimensions}
{

}

Button::~Button() noexcept
{
    m_label_ptr.reset();
}

Button::Button(const Button& other): BaseButton{other}
{
    m_label_ptr.reset(new Label(*other.m_label_ptr.get()));
}

Button::Button(Button&& other) noexcept : BaseButton{other}
{
    m_label_ptr = std::move(other.m_label_ptr);
}

Button& Button::operator=(const Button& other)
{
    if(this != &other)//not same ref
    {
        Button tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Button& Button::operator=(Button&& other) noexcept
{
    m_label_ptr = std::move(other.m_label_ptr);
    return *this;
}

//<f> Overrides IGuiInteraction
void Button::Input(const SDL_Event &event)
{
    BaseButton::Input(event);
}
//</f>

//<f> Overrides GUIElement
void Button::Logic(float fixed_delta_time)
{
    BaseButton::Logic(fixed_delta_time);
}
//</f>

//<f> Overrides IGuiRender
void Button::Render(float delta_time)
{
    if(!m_render)
    return;

    BaseButton::Render(delta_time);

    if(m_label_ptr)
        m_label_ptr->Render(delta_time);
}
//</f>

/* < Virtual Methods > */
void Button::CreateLabel(const std::string& text, const std::string& font_path, int font_size, const SDL_Colour& text_colour, Position local_position)
{
    m_label_ptr.reset(new Label(m_renderer_ptr, m_resource_manager_ptr, font_path, font_size, text, text_colour, local_position));
    m_label_ptr->TransformPtr()->Parent(this->TransformPtr());
    m_label_ptr->TransformPtr()->LocalPosition(local_position);
}
/* </ Virtual Methods > */

}//namespace

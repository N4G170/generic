#include "sdl_gui_button.hpp"
#include "sdl_gui_constants.hpp"
#include <utility>
#include <string>
#include <SDL2/SDL_image.h>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

Button::Button(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions): GuiElement{resource_manager_ptr, renderer_ptr, position, dimensions},
    m_transition_type{ButtonTransitionType::COLOUR}, m_current_texture{}, m_base_colour_texture{m_resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    AddGuiCollider({0,0}, m_transform.BaseDimensions(), &m_transform);

    m_status_colours.insert({ButtonState::ACTIVE, {255,255,255,255}});
    m_status_colours.insert({ButtonState::INACTIVE, {255,255,255,128}});
    m_status_colours.insert({ButtonState::HOVER, {200,200,200,255}});
    m_status_colours.insert({ButtonState::DOWN, {145,145,145,255}});

    // m_status_texture.insert({ButtonState::ACTIVE, m_resource_manager_ptr->GetTexture(c_button_base)});
    // m_status_texture.insert({ButtonState::INACTIVE, m_resource_manager_ptr->GetTexture(c_button_base)});
    // m_status_texture.insert({ButtonState::HOVER, m_resource_manager_ptr->GetTexture(c_button_base)});
    // m_status_texture.insert({ButtonState::DOWN, m_resource_manager_ptr->GetTexture(c_button_base)});
}

Button::~Button() noexcept
{
    m_label_ptr.reset();
}

Button::Button(const Button& other): GuiElement{other}, GuiInteraction{other}, m_status_colours{other.m_status_colours}, m_transition_type{other.m_transition_type},
    m_current_texture{other.m_current_texture}, m_base_colour_texture{other.m_base_colour_texture}
{
    m_label_ptr.reset(new Label(*other.m_label_ptr.get()));
}

Button::Button(Button&& other) noexcept : GuiElement{other}, GuiInteraction{other}
{
    m_status_colours = std::move(other.m_status_colours);
    m_transition_type = std::move(other.m_transition_type);
    m_current_texture = std::move(other.m_current_texture);
    m_base_colour_texture = std::move(other.m_base_colour_texture);
    m_mouse_flags = std::move(other.m_mouse_flags);
    m_base_colour_texture = std::move(other.m_base_colour_texture);
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

/* < Overrides GUIElement > */
void Button::Logic(float fixed_delta_time)
{
    if(m_active)
    {
        m_valid_click_timer += fixed_delta_time;
        m_base_colour_texture.ColorModulation(m_status_colours[ButtonState::ACTIVE]);
        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
            m_base_colour_texture.ColorModulation(m_status_colours[ButtonState::HOVER]);
        if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
        {
            m_valid_click_timer = 0;//start click timer

            m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
            for(auto& callback : m_mouse_down_callbacks)
                callback();
        }
        else if(m_mouse_flags & MouseFlags::MOUSE_UP)
        {
            m_mouse_flags &= ~MouseFlags::MOUSE_UP;
            for(auto& callback : m_mouse_up_callbacks)
                callback();

            if(m_valid_click_timer <= 0.1)
            {
                for(auto& callback : m_mouse_click_callbacks)
                    callback();
            }
        }

        if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
        {
            m_base_colour_texture.ColorModulation(m_status_colours[ButtonState::DOWN]);
        }
    }
    else
    {
        m_base_colour_texture.ColorModulation(m_status_colours[ButtonState::INACTIVE]);
    }
}

void Button::Render(float delta_time)
{
    Render(m_renderer_ptr, delta_time);
}

void Button::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };
    // SDL_Rect dst{ 150, 150, 150, 150 };
    // SDL_SetRenderDrawColor(m_renderer_ptr, m_current_colour.r, m_current_colour.g, m_current_colour.b, m_current_colour.a);
    // SDL_RenderFillRect(m_renderer_ptr, &dst);
    if(m_transition_type == ButtonTransitionType::COLOUR)
    {
        m_base_colour_texture.Render(nullptr, &dst);
    }
    else if(m_transition_type == ButtonTransitionType::TEXTURE)
    {
        m_current_texture.Render();
    }

    if(m_label_ptr)
        m_label_ptr->Render(delta_time);

    if(m_render_bounds_border)
        RenderBorder();
}
/* </ Overrides > */

/* < Overrides GuiInteraction > */
void Button::Input(const SDL_Event &event)
{
    if( !m_active )
        return;

    bool status{ MouseInsideCollider(event.motion.x, event.motion.y) };

    if(status)//mouse inside button, we can do stuff
    {
        //enter exit button
        if(!(m_mouse_flags & MouseFlags::MOUSE_HOVER) && status)//we enter the button
            m_mouse_flags |= MouseFlags::MOUSE_ENTER;//add
        if((m_mouse_flags & MouseFlags::MOUSE_HOVER) && !status)//we exit the button
            m_mouse_flags |= MouseFlags::MOUSE_EXIT;//add

        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)//valid btn down
        {
            m_mouse_flags |= MouseFlags::MOUSE_DOWN;
            m_mouse_flags |= MouseFlags::MOUSE_HOLD_DOWN;
        }
        else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)//valid btn down
        {
            m_mouse_flags |= MouseFlags::MOUSE_UP;
            m_mouse_flags &= ~MouseFlags::MOUSE_HOLD_DOWN;
        }

        //update hover flag
        m_mouse_flags |= MouseFlags::MOUSE_HOVER;//add
    }
    else//clear flags
    {
        m_mouse_flags = MouseFlags::NONE;
    }
}
/* </ Overrides > */

/* < Getters/Setters > */
void Button::TransitionType(ButtonTransitionType type)
{
    m_transition_type = type;
}

ButtonTransitionType Button::TransitionType()
{
    return m_transition_type;
}
/* </ Getters/Setters > */

/* < Virtual Methods > */
void Button::CreateLabel(const std::string& text, const std::string& font_path, int font_size, const SDL_Colour& text_colour, Position local_position)
{
    m_label_ptr.reset(new Label(m_resource_manager_ptr, m_renderer_ptr, font_path, font_size, text, text_colour, local_position, {0,0}));
    m_label_ptr->TransformPtr()->Parent(this->TransformPtr());
    m_label_ptr->TransformPtr()->LocalPosition(local_position);
}

void Button::SetStateColour(ButtonState button_state, SDL_Colour colour)
{
    m_status_colours[button_state] = colour;
}

void Button::SetStateColours(SDL_Colour inactive, SDL_Colour active, SDL_Colour hover, SDL_Colour down)
{
    m_status_colours[ButtonState::INACTIVE] = inactive;
    m_status_colours[ButtonState::ACTIVE] = active;
    m_status_colours[ButtonState::HOVER] = hover;
    m_status_colours[ButtonState::DOWN] = down;
}

void Button::SetStateTexture(ButtonState button_state, Texture texture)
{
    m_status_texture[button_state] = texture;
}

void Button::SetStateTexture(Texture inactive, Texture active, Texture hover, Texture down)
{
    m_status_texture[ButtonState::INACTIVE] = inactive;
    m_status_texture[ButtonState::ACTIVE] = active;
    m_status_texture[ButtonState::HOVER] = hover;
    m_status_texture[ButtonState::DOWN] = down;
}
/* </ Virtual Methods > */

}//namespace

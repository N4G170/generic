#include "sdl_gui_base_button.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"

namespace sdl_gui
{


BaseButton::BaseButton(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions) :
    GuiElement{position, dimensions}, IGuiRender{renderer_ptr, resource_manager_ptr},
    m_transition_type{ButtonTransitionType::COLOUR}, m_box_texture{m_resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    AddGuiCollider({0,0}, m_transform.Size(), &m_transform);

    m_status_colours.insert({ButtonState::ACTIVE, {255,255,255,255}});
    m_status_colours.insert({ButtonState::INACTIVE, {255,255,255,128}});
    m_status_colours.insert({ButtonState::HOVER, {200,200,200,255}});
    m_status_colours.insert({ButtonState::DOWN, {145,145,145,255}});

    MouseCallback(MouseCallbackType::ACTIVE, std::bind(&BaseButton::BoxTextureColourModulation, this, std::ref(m_status_colours[ButtonState::ACTIVE])));
    MouseCallback(MouseCallbackType::INACTIVE, std::bind(&BaseButton::BoxTextureColourModulation, this, std::ref(m_status_colours[ButtonState::INACTIVE])));
    MouseCallback(MouseCallbackType::HOVER, std::bind(&BaseButton::BoxTextureColourModulation, this, std::ref(m_status_colours[ButtonState::HOVER])));
    MouseCallback(MouseCallbackType::DOWN, std::bind(&BaseButton::BoxTextureColourModulation, this, std::ref(m_status_colours[ButtonState::DOWN])));
}

BaseButton::~BaseButton() noexcept
{

}

BaseButton::BaseButton(const BaseButton& other): GuiElement{other}, IGuiRender{other}, IGuiInteraction{other},
    m_status_colours{other.m_status_colours}, m_transition_type{other.m_transition_type}, m_box_texture{other.m_box_texture}
{

}

BaseButton::BaseButton(BaseButton&& other) noexcept : GuiElement{other}, IGuiRender{other}, IGuiInteraction{other}
{
    m_status_colours = std::move(other.m_status_colours);
    m_transition_type = std::move(other.m_transition_type);
    m_box_texture = std::move(other.m_box_texture);
    m_mouse_flags = std::move(other.m_mouse_flags);
}

BaseButton& BaseButton::operator=(const BaseButton& other)
{
    if(this != &other)//not same ref
    {
        BaseButton tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

BaseButton& BaseButton::operator=(BaseButton&& other) noexcept
{
    m_status_colours = std::move(other.m_status_colours);
    m_transition_type = std::move(other.m_transition_type);
    m_box_texture = std::move(other.m_box_texture);
    m_mouse_flags = std::move(other.m_mouse_flags);

    return *this;
}

//<f> Overrides GuiInteraction
void BaseButton::Input(const SDL_Event& event)
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
        else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)//valid btn up
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
//</f>

//<f> Overrides GUIElement
void BaseButton::Logic(float delta_time)
{
    CallBacksLogic(delta_time);

    // if(m_active)
    // {
    //     m_valid_click_timer += fixed_delta_time;
    //     m_colour_texture.ColorModulation(m_status_colours[ButtonState::ACTIVE]);
    //     if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
    //         m_colour_texture.ColorModulation(m_status_colours[ButtonState::HOVER]);
    //     if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
    //     {
    //         m_valid_click_timer = 0;//start click timer
    //
    //         m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
    //         for(auto& callback : m_mouse_down_callbacks)
    //             callback();
    //     }
    //     else if(m_mouse_flags & MouseFlags::MOUSE_UP)
    //     {
    //         m_mouse_flags &= ~MouseFlags::MOUSE_UP;
    //         for(auto& callback : m_mouse_up_callbacks)
    //             callback();
    //
    //         if(m_valid_click_timer <= 0.1)
    //         {
    //             for(auto& callback : m_mouse_click_callbacks)
    //                 callback();
    //         }
    //     }
    //
    //     if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
    //     {
    //         m_colour_texture.ColorModulation(m_status_colours[ButtonState::DOWN]);
    //     }
    // }
    // else
    // {
    //     m_colour_texture.ColorModulation(m_status_colours[ButtonState::INACTIVE]);
    // }
}

//</f>

//<f> Overrides IGuiRender
void BaseButton::Render(float delta_time)
{
    if(!m_render)
    return;

    SDL_Rect dst{ m_transform.RenderRect() };
    // SDL_Rect dst{ 150, 150, 150, 150 };
    // SDL_SetRenderDrawColor(m_renderer_ptr, m_current_colour.r, m_current_colour.g, m_current_colour.b, m_current_colour.a);
    // SDL_RenderFillRect(m_renderer_ptr, &dst);
    if(m_transition_type == ButtonTransitionType::COLOUR)
    {
        m_box_texture.Render(nullptr, &dst);
    }
    else if(m_transition_type == ButtonTransitionType::TEXTURE)
    {
        m_box_texture.Render();
    }

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

//<f> Virtual Methods
void BaseButton::SetStateColour(ButtonState button_state, SDL_Colour colour)
{
    m_status_colours[button_state] = colour;
}

void BaseButton::SetStateColours(SDL_Colour inactive, SDL_Colour active, SDL_Colour hover, SDL_Colour down)
{
    m_status_colours[ButtonState::INACTIVE] = inactive;
    m_status_colours[ButtonState::ACTIVE] = active;
    m_status_colours[ButtonState::HOVER] = hover;
    m_status_colours[ButtonState::DOWN] = down;
}
//</f>

//<f> Getters/Setters
void BaseButton::TransitionType(ButtonTransitionType type)
{
    m_transition_type = type;
}

ButtonTransitionType BaseButton::TransitionType()
{
    return m_transition_type;
}
//</f>

void BaseButton::BoxTextureColourModulation(const SDL_Colour& colour)
{
    m_box_texture.ColourModulation(colour);
}
}

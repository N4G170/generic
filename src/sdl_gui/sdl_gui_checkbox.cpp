#include "sdl_gui_checkbox.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"

namespace sdl_gui
{

CheckBox::CheckBox(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions) :
    GuiElement{resource_manager_ptr, renderer_ptr, position, dimensions},
    m_is_checked{false}, m_box_texture{resource_manager_ptr->GetTexture(c_img_white_dot)},
    m_check_mark_texture{resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    AddGuiCollider({0,0}, m_transform.BaseDimensions(), &m_transform);

    m_check_mark_texture.ColorModulation(Colour::Black);

    m_status_colours.insert({ButtonState::ACTIVE, {255,255,255,255}});
    m_status_colours.insert({ButtonState::INACTIVE, {255,255,255,128}});
    m_status_colours.insert({ButtonState::HOVER, {200,200,200,255}});
    m_status_colours.insert({ButtonState::DOWN, {145,145,145,255}});
}

CheckBox::~CheckBox() noexcept
{

}

CheckBox::CheckBox(const CheckBox& other) : GuiElement{other}, GuiInteraction{other}, m_is_checked{other.m_is_checked}, m_box_texture{other.m_box_texture},
m_check_mark_texture{other.m_check_mark_texture}
{

}

CheckBox::CheckBox(CheckBox&& other) noexcept : GuiElement{other}, GuiInteraction{other}
{
    m_is_checked = std::move(other.m_is_checked);
    m_box_texture = std::move(other.m_box_texture);
    m_check_mark_texture = std::move(other.m_check_mark_texture);
}

CheckBox& CheckBox::operator=(const CheckBox& other)
{
    if(this != &other)//not same ref
    {
        CheckBox tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

CheckBox& CheckBox::operator=(CheckBox&& other) noexcept
{
    m_is_checked = std::move(other.m_is_checked);
    m_box_texture = std::move(other.m_box_texture);
    m_check_mark_texture = std::move(other.m_check_mark_texture);

    return *this;
}

// <f> Overrides GUIElement
void CheckBox::Logic(float fixed_delta_time)
{
    if(m_active)
    {
        m_valid_click_timer += fixed_delta_time;
        m_box_texture.ColorModulation(m_status_colours[ButtonState::ACTIVE]);
        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
            m_box_texture.ColorModulation(m_status_colours[ButtonState::HOVER]);
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

                m_is_checked = !m_is_checked;
            }
        }

        if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
        {
            m_box_texture.ColorModulation(m_status_colours[ButtonState::DOWN]);
        }
    }
    else
    {
        m_box_texture.ColorModulation(m_status_colours[ButtonState::INACTIVE]);
    }
}

void CheckBox::Render(float delta_time)
{
    Render(m_renderer_ptr, delta_time);
}

void CheckBox::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };
    // SDL_Rect dst{ 150, 150, 150, 150 };
    // SDL_SetRenderDrawColor(m_renderer_ptr, m_current_colour.r, m_current_colour.g, m_current_colour.b, m_current_colour.a);
    // SDL_RenderFillRect(m_renderer_ptr, &dst);
    m_box_texture.Render(nullptr, &dst);

    if(m_render_bounds_border)
        RenderBorder();

    //calculate checkmark coordinates and dimensions//TMP
    int check_w{dst.w/3};
    int check_h{dst.w/3};

    dst.x = dst.x + (dst.w - check_w) / 2;
    dst.y = dst.y + (dst.h - check_h) / 2;

    dst.w = check_w;
    dst.h = check_h;

    if(m_is_checked)
        m_check_mark_texture.Render(nullptr, &dst);
}
// </f>

// <f> Overrides GuiInteraction
void CheckBox::Input(const SDL_Event& event)
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
//</f>

}//namespace

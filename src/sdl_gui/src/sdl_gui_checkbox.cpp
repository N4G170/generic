#include "sdl_gui_checkbox.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

CheckBox::CheckBox(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions, int value) :
    BaseButton{renderer_ptr, resource_manager_ptr, position, dimensions},
    m_is_checked{false}, m_check_mark_texture{resource_manager_ptr->GetTexture(c_img_white_dot)}, m_value{value}
{
    AddGuiCollider({0,0}, m_transform.Size(), &m_transform);

    m_check_mark_texture.ColourModulation(Colour::Black);

    MouseCallback(MouseCallbackType::CLICK, std::bind(&CheckBox::MouseClick, this));
}

CheckBox::~CheckBox() noexcept
{

}

CheckBox::CheckBox(const CheckBox& other) : BaseButton{other}, m_is_checked{other.m_is_checked},
m_check_mark_texture{other.m_check_mark_texture}, m_value{other.m_value}
{

}

CheckBox::CheckBox(CheckBox&& other) noexcept : BaseButton{other}
{
    m_is_checked = std::move(other.m_is_checked);
    m_check_mark_texture = std::move(other.m_check_mark_texture);
    m_value= std::move(other.m_value);
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
    this->m_is_checked = std::move(other.m_is_checked);
    this->m_check_mark_texture = std::move(other.m_check_mark_texture);
    this->m_value = std::move(other.m_value);

    return *this;
}

//<f> Overrides IGuiInteraction
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

//<f> Overrides GUIElement
// void CheckBox::Logic(float fixed_delta_time)
// {
//     if(m_active)
//     {
//         m_valid_click_timer += fixed_delta_time;
//         m_box_texture.ColorModulation(m_status_colours[ButtonState::ACTIVE]);
//
//         if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
//             m_box_texture.ColorModulation(m_status_colours[ButtonState::HOVER]);
//
//         if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
//         {
//             m_valid_click_timer = 0;//start click timer
//
//             m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
//             for(auto& callback : m_mouse_down_callbacks)
//                 callback();
//         }
//         else if(m_mouse_flags & MouseFlags::MOUSE_UP)
//         {
//             m_mouse_flags &= ~MouseFlags::MOUSE_UP;
//             for(auto& callback : m_mouse_up_callbacks)
//                 callback();
//
//             if(m_valid_click_timer <= 0.25)
//             {
//                 for(auto& callback : m_mouse_click_callbacks)
//                     callback();
//
//                 //change value
//
//             }
//         }
//
//         if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
//         {
//             m_box_texture.ColorModulation(m_status_colours[ButtonState::DOWN]);
//         }
//     }
//     else
//     {
//         m_box_texture.ColorModulation(m_status_colours[ButtonState::INACTIVE]);
//     }
// }
// </f>

//<f> Overrides IGuiRender
void CheckBox::Render(float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };
    // SDL_Rect dst{ 150, 150, 150, 150 };
    // Log(std::to_string(m_box_texture.ColorModulation().r)+" - ");
    // Log(std::to_string(m_box_texture.ColorModulation().g)+" - ");
    // Log(std::to_string(m_box_texture.ColorModulation().b)+" - ");
    // Log(std::to_string(m_box_texture.ColorModulation().a)+"\n");
    // SDL_SetRenderDrawColor(m_renderer_ptr, m_box_texture.ColorModulation().r, m_box_texture.ColorModulation().g, m_box_texture.ColorModulation().b, m_box_texture.ColorModulation().a);
    // SDL_RenderFillRect(m_renderer_ptr, &dst);
    m_box_texture.Render(nullptr, &dst);

    //calculate checkmark coordinates and dimensions//TMP
    int check_w{dst.w/3};
    int check_h{dst.w/3};

    dst.x = dst.x + (dst.w - check_w) / 2;
    dst.y = dst.y + (dst.h - check_h) / 2;

    dst.w = check_w;
    dst.h = check_h;

    if(m_is_checked)
        m_check_mark_texture.Render(nullptr, &dst);

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

void CheckBox::MouseClick()
{
    m_is_checked = !m_is_checked;

    if(ValueChanged)
        ValueChanged(this);
}

}//namespace

#include "sdl_gui_textbox.hpp"
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"
#include "sdl_gui_utils.hpp"
#include <utility>

namespace sdl_gui
{

//<f> Constructors & operator=
Textbox::Textbox(GuiMainPointers main_pointers, const Position& position, const Dimensions& size) :
    GuiElement{main_pointers, position, size}, m_bg_texture{m_main_pointers.resource_manager_ptr->GetTexture(c_img_white_dot)},
    m_text_label{main_pointers, position, size}
{
    AddGuiCollider({0,0}, Size(), &m_transform);

    m_edit_field_rect = RectFromStructs(position, size);
    // m_text_label.RenderBorder(true);
    m_text_label.Parent(this);
    m_text_label.TransformPtr()->ParentViewport(&m_transform);
    CentreLabel();
}

Textbox::~Textbox() noexcept
{

}

Textbox::Textbox(const Textbox& other) : GuiElement{other}, m_bg_texture{other.m_bg_texture}, m_text_label{other.m_text_label}
{

}

Textbox::Textbox(Textbox&& other) noexcept : GuiElement{other}, m_bg_texture{std::move(other.m_bg_texture)}, m_text_label{std::move(other.m_text_label)}
{

}

Textbox& Textbox::operator=(const Textbox& other)
{
    if(this != &other)//not same ref
    {
        Textbox tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Textbox& Textbox::operator=(Textbox&& other) noexcept
{
    return *this;
}
//</f>

//<f> Overrides GUIElement
// void Textbox::Input(const SDL_Event& event)
// {
//     if( !m_active )
//         return;
//
//     bool status{ MouseInsideCollider(event.motion.x, event.motion.y) };
//
//
//     if(status)//mouse inside button, we can do stuff
//     {
//         //enter exit button
//         if(!(m_mouse_flags & MouseFlags::MOUSE_HOVER) && status)//we enter the button
//         m_mouse_flags |= MouseFlags::MOUSE_ENTER;//add
//         if((m_mouse_flags & MouseFlags::MOUSE_HOVER) && !status)//we exit the button
//         m_mouse_flags |= MouseFlags::MOUSE_EXIT;//add
//
//         if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)//valid btn down
//         {
//             m_mouse_flags |= MouseFlags::MOUSE_DOWN;
//             m_mouse_flags |= MouseFlags::MOUSE_HOLD_DOWN;
//         }
//         else if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)//valid btn up
//         {
//             m_mouse_flags |= MouseFlags::MOUSE_UP;
//             m_mouse_flags &= ~MouseFlags::MOUSE_HOLD_DOWN;
//         }
//
//         //update hover flag
//         m_mouse_flags |= MouseFlags::MOUSE_HOVER;//add
//     }
//     else//clear flags
//     {
//         m_mouse_flags = MouseFlags::NONE;
//     }
// }

// void Textbox::Logic(float fixed_delta_time)
// {
//     if(m_active)
//     {
//         if(m_mouse_callbacks[MouseCallbackType::ACTIVE])
//             m_mouse_callbacks[MouseCallbackType::ACTIVE]();
//
//         m_valid_click_timer += fixed_delta_time;
//
//         if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
//         {
//             if(m_mouse_callbacks[MouseCallbackType::HOVER])
//                 m_mouse_callbacks[MouseCallbackType::HOVER]();
//         }
//         if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
//         {
//             m_valid_click_timer = 0;//start click timer
//
//             m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
//             if(m_mouse_callbacks[MouseCallbackType::DOWN])
//                 m_mouse_callbacks[MouseCallbackType::DOWN]();
//         }
//         else if(m_mouse_flags & MouseFlags::MOUSE_UP)
//         {
//             m_mouse_flags &= ~MouseFlags::MOUSE_UP;
//             if(m_mouse_callbacks[MouseCallbackType::UP])
//                 m_mouse_callbacks[MouseCallbackType::UP]();
//
//             if(m_valid_click_timer <= 0.25)
//             {
//                 if(m_mouse_callbacks[MouseCallbackType::CLICK])
//                     m_mouse_callbacks[MouseCallbackType::CLICK]();
//             }
//         }
//
//         if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
//         {
//             if(m_mouse_callbacks[MouseCallbackType::HOLD])
//                 m_mouse_callbacks[MouseCallbackType::HOLD]();
//         }
//     }
//     else
//     {
//         if(m_mouse_callbacks[MouseCallbackType::INACTIVE])
//             m_mouse_callbacks[MouseCallbackType::INACTIVE]();
//     }
// }

void Textbox::Render(float delta_time)
{
    Render(delta_time, m_main_pointers.main_camera_ptr);
}

void Textbox::Render(float delta_time, Camera* camera)
{
    if(!m_render)
        return;

    SDL_Rect dst{RenderRect()};

    //apply camera position
    dst.x += camera->CameraPosition().x;
    dst.y += camera->CameraPosition().y;

    if(camera->RectInsideCamera(dst))
    {
        m_bg_texture.Render(nullptr, &dst);

        m_edit_field_rect = {dst.x + 5, dst.y + 5, dst.w - 10, dst.h - 10};

        //set viewport
        SDL_RenderSetViewport(m_main_pointers.main_renderer_ptr, &m_edit_field_rect);
        m_text_label.Render(delta_time);
        SDL_RenderSetViewport(m_main_pointers.main_renderer_ptr, nullptr);

        SDL_RenderDrawRect(m_main_pointers.main_renderer_ptr, &m_edit_field_rect);
    }

}
//</f>

//<f> Private Methods
void Textbox::CentreLabel()
{
    // int border{10};//in pixels

    Position position{m_text_label.TransformPtr()->LocalPosition()};
    Dimensions dimensions{m_text_label.Size()};

    // position.x = border;
    position.y = m_edit_field_rect.h/2 - dimensions.h/2;
    // position.y = m_transform.Size().h/2 - dimensions.h/2;
    // m_text_label.LineLength( m_transform.Size().w - border * 2 );
    // dimensions.h = m_transform.Size().h - border * 2;

    m_text_label.TransformPtr()->LocalPosition(position);
    // m_text_label.TransformPtr()->Size(dimensions);
}
//</f>

}//namespace

#include "sdl_gui_textbox.hpp"
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"
#include <utility>

namespace sdl_gui
{


//<f> Constructors & operator=
Textbox::Textbox(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions) :
    GuiElement{position, dimensions}, IGuiRender{renderer_ptr, resource_manager_ptr}, m_bg_texture{m_resource_manager_ptr->GetTexture(c_img_white_dot)},
    m_text_label{renderer_ptr, resource_manager_ptr, c_default_font, c_default_font_size, "const std::string& text Error setting cenas", Colour::Black, position}
{
    AddGuiCollider({0,0}, m_transform.Size(), &m_transform);

    m_edit_field_rect = {position.x + 5, position.y + 5, dimensions.w - 10, dimensions.h - 10};
    // m_text_label.RenderBorder(true);
    m_text_label.TransformPtr()->Parent(&m_transform);
    m_text_label.TransformPtr()->ParentViewport(&m_transform);
    CentreLabel();
}

Textbox::~Textbox() noexcept
{

}

Textbox::Textbox(const Textbox& other) : GuiElement{other}, IGuiRender{other}, IGuiInteraction{other}, m_bg_texture{other.m_bg_texture}, m_text_label{other.m_text_label}
{

}

Textbox::Textbox(Textbox&& other) noexcept : GuiElement{other}, IGuiRender{other}, IGuiInteraction{other},
    m_bg_texture{std::move(other.m_bg_texture)}, m_text_label{std::move(other.m_text_label)}
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

//<f> Overrides IGuiInteraction
void Textbox::Input(const SDL_Event& event)
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
void Textbox::Logic(float fixed_delta_time)
{
    if(m_active)
    {
        if(m_mouse_callbacks[MouseCallbackType::ACTIVE])
            m_mouse_callbacks[MouseCallbackType::ACTIVE]();

        m_valid_click_timer += fixed_delta_time;

        if(m_mouse_flags & MouseFlags::MOUSE_HOVER)
        {
            if(m_mouse_callbacks[MouseCallbackType::HOVER])
                m_mouse_callbacks[MouseCallbackType::HOVER]();
        }
        if(m_mouse_flags & MouseFlags::MOUSE_DOWN)
        {
            m_valid_click_timer = 0;//start click timer

            m_mouse_flags &= ~MouseFlags::MOUSE_DOWN;
            if(m_mouse_callbacks[MouseCallbackType::DOWN])
                m_mouse_callbacks[MouseCallbackType::DOWN]();
        }
        else if(m_mouse_flags & MouseFlags::MOUSE_UP)
        {
            m_mouse_flags &= ~MouseFlags::MOUSE_UP;
            if(m_mouse_callbacks[MouseCallbackType::UP])
                m_mouse_callbacks[MouseCallbackType::UP]();

            if(m_valid_click_timer <= 0.25)
            {
                if(m_mouse_callbacks[MouseCallbackType::CLICK])
                    m_mouse_callbacks[MouseCallbackType::CLICK]();
            }
        }

        if(m_mouse_flags & MouseFlags::MOUSE_HOLD_DOWN)
        {
            if(m_mouse_callbacks[MouseCallbackType::HOLD])
                m_mouse_callbacks[MouseCallbackType::HOLD]();
        }
    }
    else
    {
        if(m_mouse_callbacks[MouseCallbackType::INACTIVE])
            m_mouse_callbacks[MouseCallbackType::INACTIVE]();
    }
}
// </f>

//<f> Overrides IGuiRender
void Textbox::Render(float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };

    m_bg_texture.Render(nullptr, &dst);

    m_edit_field_rect = {dst.x + 5, dst.y + 5, dst.w - 10, dst.h - 10};

    //set viewport
    SDL_RenderSetViewport(m_renderer_ptr, &m_edit_field_rect);
    m_text_label.Render(delta_time);
    SDL_RenderSetViewport(m_renderer_ptr, nullptr);

    SDL_RenderDrawRect(m_renderer_ptr, &m_edit_field_rect);

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

//<f> Private Methods
void Textbox::CentreLabel()
{
    // int border{10};//in pixels

    Position position{m_text_label.TransformPtr()->LocalPosition()};
    Dimensions dimensions{m_text_label.TransformPtr()->Size()};

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

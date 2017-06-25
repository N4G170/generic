#include "sdl_gui_label.hpp"
#include "sdl_gui_texture_utils.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

// Label::Label(): IGuiRender{}, m_text_texture{}, m_text{""}, m_text_colour{0,0,0,255}, m_font_ptr{nullptr}
// {
//     m_renderer_ptr = nullptr;
// }

Label::Label(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, const std::string& font_path, int font_size, const std::string& text, const SDL_Colour& text_colour, Position position):
    GuiElement{position, {0,0}}, IGuiRender{renderer_ptr, resource_manager_ptr}, m_text_texture{m_renderer_ptr,0,0}, m_text{text}, m_text_colour{text_colour}
{
    m_font_ptr = m_resource_manager_ptr->GetFont(font_path, font_size);
    m_line_length=0;
    //Sets the new text and resizes the texture if needed
    Text(m_text, m_text_colour);
}

Label::Label(SDL_Renderer* renderer, ResourceManager* resource_manager_ptr, Font* font_ptr, const std::string& text, const SDL_Colour& text_colour, Position position)
{
    m_font_ptr = nullptr;
}

Label::~Label() noexcept
{

}

Label::Label(const Label& other):m_text_texture{other.m_text_texture}, m_text{other.m_text}, m_text_colour{other.m_text_colour},
    m_font_ptr{other.m_font_ptr}
{
    m_renderer_ptr = other.m_renderer_ptr;
}

Label::Label(Label&& other) noexcept
{
    this->m_text_texture = std::move(other.m_text_texture);
    this->m_text = std::move(other.m_text);
    this->m_text_colour = std::move(other.m_text_colour);
    this->m_font_ptr = std::move(other.m_font_ptr);
    this->m_renderer_ptr = std::move(other.m_renderer_ptr);
}

Label& Label::operator=(const Label& other)
{
    if(this != &other)//not same ref
    {
        Label tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Label& Label::operator=(Label&& other) noexcept
{
    this->m_text_texture = std::move(other.m_text_texture);
    this->m_text = std::move(other.m_text);
    this->m_text_colour = std::move(other.m_text_colour);
    this->m_font_ptr = std::move(other.m_font_ptr);
    this->m_renderer_ptr = std::move(other.m_renderer_ptr);

    return *this;
}

//<f> Overrides GUIElement
void Label::Logic(float delta_time)
{

}
//</f>

//<f> Overrides IGuiRender
void Label::Render(float delta_time)
{
    SDL_Rect src{ m_transform.RenderRect() };
    SDL_Rect dst{ m_transform.RenderRect() };

    src.x = src.y = 0;

    if(m_line_length > 0)
    {
        src.w = m_line_length;
        dst.w = m_line_length;
        // m_border_rect.w = m_line_length;
    }

    m_text_texture.Render(&src, &dst);//cut overflow
    // m_text_texture.Render(nullptr, &dst);

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

//<f> Getters/Setters
std::string Label::Text()
{
    return m_text;
}

void Label::Text(const std::string& text, const SDL_Colour& text_colour)
{
    m_text_colour = text_colour;
    int w{0}, h{0};
    m_font_ptr->CalculateTextTextureSize(text, &w, &h, m_line_length);
    Dimensions size{m_transform.Size()};

    if(w > size.w || h > size.h)//current texture is too small
    {
        m_transform.Size({w,h});
        m_text_texture.TexturePtr(CreateSDLTexture(m_renderer_ptr, w,h));
    }
    else
    {
        m_text_texture.Clear();
    }

    m_font_ptr->StringTexture(text, 0, 0, text_colour, m_text_texture.TexturePtr());

    m_border_rect = m_transform.RenderRect();
}

void Label::LineLength(int line_length)
{
    m_line_length = line_length;
    //rebuild texture
    Text(m_text, m_text_colour);
}

//</f>
}//namespace

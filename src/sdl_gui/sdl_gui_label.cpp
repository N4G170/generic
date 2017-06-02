#include "sdl_gui_label.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

Label::Label():m_text_texture{nullptr}, m_bg_texture{nullptr}, m_text{""}, m_text_colour{}, m_font_ptr{nullptr}
{
    m_renderer_ptr = nullptr;
}

Label::Label(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, const std::string& font_path, int font_size, const std::string& text, const SDL_Colour& text_colour, Position position, Dimensions dimensions):
    GuiElement{resource_manager_ptr, renderer_ptr, position, dimensions}, m_text_texture{nullptr}, m_text{text}, m_text_colour{text_colour}
{

    m_font_ptr = new Font(renderer_ptr, font_path, font_size);
    m_transform.BaseDimensions({250,50});
    // m_position_and_size.w = w;
    // m_position_and_size.h = h;

    m_text_texture = SDL_CreateTexture(m_renderer_ptr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 250, 50);
    m_font_ptr->StringTexture(text, 0, 0, text_colour, m_text_texture);
}

Label::~Label() noexcept
{
    delete m_font_ptr;
    m_font_ptr = nullptr;
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

/* < Overrides GUIElement > */
void Label::Render(float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };
    SDL_RenderCopy(m_renderer_ptr, m_text_texture, nullptr, &dst);
}

void Label::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_Rect dst{ m_transform.RenderRect() };
    SDL_RenderCopy(renderer, m_text_texture, nullptr, &dst);
}

void Label::Logic(float fixed_delta_time)
{

}

/* </ Overrides > */

std::string Label::Text()
{
    return m_text;
}

void Label::Text(const std::string& text, SDL_Colour text_colour)
{
    m_text_colour = text_colour;
    SDL_DestroyTexture(m_text_texture);
    m_text_texture = SDL_CreateTexture(m_renderer_ptr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 250, 50);
    m_font_ptr->StringTexture(text, 0, 0, text_colour, m_text_texture);
}

}//namespace

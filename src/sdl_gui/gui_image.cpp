#include "gui_image.hpp"
#include <utility>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace sdl_gui
{

GuiImage::GuiImage(SDL_Renderer* renderer_ptr, const std::string& texture_path, Position position): GuiElement{renderer_ptr, position, {0,0}}
{
    std::cout << "NORMAL" << "\n";
    m_texture = SDL_CreateTextureFromSurface(renderer_ptr, IMG_Load(texture_path.data()));

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_dimensions.w, &m_dimensions.h);
}

GuiImage::~GuiImage() noexcept
{

}

GuiImage::GuiImage(const GuiImage& other)
{
    std::cout << "COPY" << "\n";
}

GuiImage::GuiImage(GuiImage&& other) noexcept
{
    std::cout << "MOVE" << "\n";
}

GuiImage& GuiImage::operator=(const GuiImage& other)
{
    std::cout << "COPY=" << "\n";
    if(this != &other)//not same ref
    {
        GuiImage tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiImage& GuiImage::operator=(GuiImage&& other) noexcept
{
    std::cout << "MOVE=" << "\n";
    return *this;
}

/* < Overrides GUIElement > */
void GuiImage::Render()
{
    SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    // SDL_RenderCopy(m_renderer_ptr, m_texture, nullptr, &dst);
    SDL_RenderFillRect(m_renderer_ptr, &dst);
}

void GuiImage::Render(SDL_Renderer* renderer)
{
    // SDL_Rect dst{ m_position.x, m_position.y, m_dimensions.w, m_dimensions.h };
    SDL_RenderCopy(m_renderer_ptr, m_texture, nullptr, nullptr);
    // SDL_RenderCopy(renderer, m_text_texture, nullptr, &dst);
}

void GuiImage::Logic()
{

}
/* </ Overrides > */

}//namespace

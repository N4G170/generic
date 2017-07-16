#include "sdl_gui_image.hpp"
#include <utility>

namespace sdl_gui
{

//<f> Constructors & operator=
Image::Image(GuiMainPointers main_pointers, const Position& position, const Dimensions& size) : GuiElement{main_pointers, position, size}, m_source_rect{nullptr} {}

Image::~Image() noexcept
{
    if(m_source_rect)
        delete(m_source_rect);
    m_source_rect = nullptr;
}

Image::Image(const Image& other): GuiElement{other}
{
    if(other.m_source_rect)
    {
        m_source_rect = new SDL_Rect{0,0,0,0};
        *m_source_rect = *other.m_source_rect;
    }
}

Image::Image(Image&& other) noexcept: GuiElement{other}, m_source_rect{std::move(other.m_source_rect)} {}

Image& Image::operator=(const Image& other)
{
    if(this != &other)//not same ref
    {
        Image tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
    return *this;
}
//</f>

//<f> Overrides GuiElement
void Image::Input(const SDL_Event& event)
{

}

void Image::FixedLogic(float fixed_delta_time)
{

}

void Image::Logic(float delta_time)
{

}

void Image::Render(float delta_time)
{
    Render(delta_time, m_main_pointers.main_camera_ptr);
}

void Image::Render(float delta_time, Camera* camera)
{
    SDL_Rect dst{RenderRect()};

    //apply camera position
    if(!m_transform.ParentViewport())//if inside viewport we cant add camera position
    {
        dst.x += camera->CameraPosition().x;
        dst.y += camera->CameraPosition().y;
    }

    if(camera->RectInsideCamera(dst))
        m_texture.Render(m_source_rect, &dst);
}
//</f>
}//namespace

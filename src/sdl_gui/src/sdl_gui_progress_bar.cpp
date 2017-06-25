#include "sdl_gui_progress_bar.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

//<f> Constructors & operator=
ProgressBar::ProgressBar(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions) :
    GuiElement{position, dimensions}, IGuiRender{renderer_ptr, resource_manager_ptr},
    m_bg_texture{m_resource_manager_ptr->GetTexture(c_img_white_dot)}, m_bar_texture{m_resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    m_bg_texture.ColourModulation({0,0,0,255});

    m_max_value = 100;
    m_min_value = 0;
    m_value = 0;

    m_bar_direction = ProgressBarDirection::RIGHT;
}

ProgressBar::~ProgressBar() noexcept
{

}

ProgressBar::ProgressBar(const ProgressBar& other)
{

}

ProgressBar::ProgressBar(ProgressBar&& other) noexcept
{

}

ProgressBar& ProgressBar::operator=(const ProgressBar& other)
{
    if(this != &other)//not same ref
    {
        ProgressBar tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ProgressBar& ProgressBar::operator=(ProgressBar&& other) noexcept
{
    return *this;
}
//</f>

//<f> Overrides IGuiRender
void ProgressBar::Render(float delta_time)
{
    SDL_Rect dst{m_transform.RenderRect()};

    m_bg_texture.Render(nullptr, &dst);

    switch(m_bar_direction)
    {
        case ProgressBarDirection::LEFT: RenderLeft(); break;
        case ProgressBarDirection::RIGHT: RenderRight(); break;
        case ProgressBarDirection::UP: RenderUp(); break;
        case ProgressBarDirection::DOWN: RenderDown(); break;
    }

    if(m_render_border)
        RenderBorder(delta_time);
}
//</f>

void ProgressBar::RenderLeft()
{
    SDL_Rect dst{m_transform.RenderRect()};
    int ten_percent{dst.w/10 > dst.h/10 ? dst.h/10 : dst.w/10};

    int prev_w = dst.w;
    dst.w =  (dst.w - (ten_percent * 2)) * (float)m_value/m_max_value;
    dst.x += prev_w - ten_percent - dst.w;

    dst.y += ten_percent;
    dst.h -= (ten_percent * 2);

    m_bar_texture.Render(nullptr, &dst);
}

void ProgressBar::RenderRight()
{
    SDL_Rect dst{m_transform.RenderRect()};
    int ten_percent{dst.w/10 > dst.h/10 ? dst.h/10 : dst.w/10};

    dst.x += ten_percent;
    dst.w =  (dst.w - (ten_percent * 2)) * (float)m_value/m_max_value;

    dst.y += ten_percent;
    dst.h -= (ten_percent * 2);

    m_bar_texture.Render(nullptr, &dst);
}

void ProgressBar::RenderUp()
{
    SDL_Rect dst{m_transform.RenderRect()};
    int ten_percent{dst.w/10 > dst.h/10 ? dst.h/10 : dst.w/10};

    dst.x += ten_percent;
    dst.w -= (ten_percent * 2);

    int prev_h = dst.h;
    dst.h = (dst.h - (ten_percent * 2)) * (float)m_value/m_max_value;
    dst.y += prev_h - ten_percent - dst.h;

    m_bar_texture.Render(nullptr, &dst);
}

void ProgressBar::RenderDown()
{
    SDL_Rect dst{m_transform.RenderRect()};
    int ten_percent{dst.w/10 > dst.h/10 ? dst.h/10 : dst.w/10};

    dst.x += ten_percent;
    dst.w -= (ten_percent * 2);

    dst.y += ten_percent;
    dst.h = (dst.h - (ten_percent * 2)) * (float)m_value/m_max_value;

    m_bar_texture.Render(nullptr, &dst);
}

}//namespace

#include "drop.hpp"
#include "constants.hpp"
#include <iostream>
#include "random.hpp"

Drop::Drop(const std::function<void()>& drop_sound):m_drop_sound{drop_sound}
{
    m_colour = Colour::Rain_Drop_Blue;
    NewStartPosition();

    m_splash_time = 1;
    m_show_splash = false;
}

void Drop::Logic(float delta_time)
{
    //physics
    m_transform.PositionY( m_transform.PositionY() + std::max(1, static_cast<int>(m_velocity * delta_time)) );

    //splash
    if(m_transform.PositionY() > window_height)
    {
        if(m_z_index < 5)//first five layers
        {
            m_splash = DimensionsRect();
            m_splash_time = 0;
            m_show_splash = true;
            if(m_z_index < 1)
                m_drop_sound();
        }

        NewStartPosition();
    }
}

void Drop::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_SetRenderDrawColor( renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a );
    SDL_Rect rect = DimensionsRect();
    SDL_RenderFillRect(renderer, &rect);

    if(m_show_splash)
    {
        int x1 {m_splash.x - m_splash.w}; int y1 {window_height - m_splash.h / 2};
        int x2 {m_splash.x}; int y2 {window_height};
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2 );

        x1 = m_splash.x + m_splash.w + m_splash.w;
        x2 = m_splash.x + m_splash.w;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2 );
    }

    m_splash_time += delta_time;
    if(m_splash_time > 0.2 && m_show_splash)
    {
        m_show_splash = false;
    }
}

void Drop::NewStartPosition()
{
    m_z_index = Random(0,15);

    m_transform.Width( 3 - static_cast<int>(m_z_index / 5) );
    m_transform.Height( std::max(1, 10 - (static_cast<int>(m_z_index / 3) * 2) ) );

    m_transform.PositionX( Random(0, window_width - m_transform.Height()) );
    //the left parameter is negative
    m_transform.PositionY( Random(-1 * m_transform.Height() - window_height, m_transform.Height()) );

    m_velocity = (20 - m_z_index) * 50;
}

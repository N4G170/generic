#include "celestial_body.hpp"
#include "shapes.hpp"
#include <algorithm>
#include <iostream>
#include "orbits.hpp"
#include "random.hpp"

CelestialBody::CelestialBody(): Object(), m_parent{nullptr}, m_radius{0}, m_current_orbit_position{0}, m_orbit_time{0}, m_orbit_wait_time{0}
{
    m_body_points.clear();
}

CelestialBody::~CelestialBody()
{

}

void CelestialBody::Configure(CelestialBodies type, CelestialBody* parent)
{
    m_parent = parent;
    m_body_points.clear();

    switch (type)
    {
        case CelestialBodies::SUN:
            GenerateCircleFirstOctantSDLPoints(sun_radius, m_body_points);
            m_colour = Colour::White;
            GenerateOrbit(m_orbit, (sun_radius + 10), (sun_radius + 10));
            m_transform.Position(0,0);
            m_current_orbit_position = 0;
            m_orbit_wait_time = 0.01f;
            m_radius = sun_radius;
        break;
        case CelestialBodies::SUN2:
            GenerateCircleFirstOctantSDLPoints(sun_radius, m_body_points);
            m_colour = Colour::White;
            GenerateOrbit(m_orbit, (sun_radius + 10), (sun_radius + 10));
            m_transform.Position(0,0);
            m_current_orbit_position = m_orbit.size()/2;
            m_orbit_wait_time = 0.01f;
            m_radius = sun_radius;
        break;

        case CelestialBodies::MERCURY:
            GenerateCircleFirstOctantSDLPoints(mercury_radius, m_body_points);
            m_colour = Colour::Grey;
            GenerateOrbit(m_orbit, (sun_radius * 3), (sun_radius * 3) * 1.517f);
            m_current_orbit_position = Random(0, m_orbit.size()-1);

            m_transform.Position(0,0);;
            m_orbit_wait_time = 0.166f;
            m_radius = mercury_radius;
        break;

        case CelestialBodies::VENUS:
            GenerateCircleFirstOctantSDLPoints(venus_radius, m_body_points);
            //m_colour = Colour::Venus_Yellow;
            m_colour = Colour::Venus_Yellow;
            GenerateOrbit(m_orbit, (sun_radius * 5), (sun_radius * 5) * 1.0136f);
            m_current_orbit_position = Random(0, m_orbit.size()-1);

            std::reverse(m_orbit.begin(), m_orbit.end());

            m_transform.Position(0,0);;

            m_orbit_wait_time = 0.611f;
            m_radius = venus_radius;
        break;

        case CelestialBodies::TERRA:
            GenerateCircleFirstOctantSDLPoints(terra_radius, m_body_points);
            //m_colour = Colour::Venus_Yellow;
            m_colour = Colour::Light_Blue;
            GenerateOrbit(m_orbit, (sun_radius * 10), (sun_radius * 10) * 1.033f, 0.015);
            m_current_orbit_position = Random(0, m_orbit.size()-1);

            m_transform.Position(0,0);

            m_orbit_wait_time = 0.611f;
            m_radius = terra_radius;
        break;

        case CelestialBodies::LUNA:
        {
            GenerateCircleFirstOctantSDLPoints(mercury_radius, m_body_points);
            //m_colour = Colour::Venus_Yellow;
            m_colour = Colour::Grey;
            GenerateOrbit(m_orbit, (terra_radius * 2), (terra_radius * 2) * 1.116f, 0.15);

            std::reverse(m_orbit.begin(), m_orbit.end());

            m_current_orbit_position = Random(0, m_orbit.size()-1);

            m_transform.Position(0,0);

            m_orbit_wait_time = 0.77f;
            m_radius = mercury_radius;
        }
        break;
        case CelestialBodies::XENO:
        {
            GenerateCircleFirstOctantSDLPoints(xeno_radius, m_body_points);
            //m_colour = Colour::Venus_Yellow;
            m_colour = Colour::Red;
            GenerateOrbit(m_orbit, (sun_radius * 12), (sun_radius * 6), 0.02);

            m_current_orbit_position = Random(0, m_orbit.size()-1);

            m_transform.Position(0,sun_radius*3);

            m_orbit_wait_time = 0.1f;
            m_radius = xeno_radius;
        }
        break;

        default:
            m_transform.Position(window_centre_x, window_centre_y);
            m_radius = 0;
        break;
    }
}

Vector2<float> CelestialBody::AjustedPosition()
{
    Vector2<float> position { m_transform.Position() };

    if(m_orbit.size() > 0)
    {
        if(m_parent != nullptr)
        {
            position.X( m_transform.PositionX() + m_orbit[m_current_orbit_position].X() + m_parent->m_transform.PositionX());
            position.Y( m_transform.PositionY() + m_orbit[m_current_orbit_position].Y() + m_parent->m_transform.PositionY());
        }
        else
        {
            position.X( m_transform.PositionX() + m_orbit[m_current_orbit_position].X() );
            position.Y( m_transform.PositionY() + m_orbit[m_current_orbit_position].Y() );
        }
    }

    return position;
}

void CelestialBody::Move(float fixed_frame_time)
{
    // if(m_parent != nullptr)
    // {
    //
    // }
    if(m_orbit_time > m_orbit_wait_time)
    {
        m_orbit_time = 0;
        ++m_current_orbit_position;
        if(m_current_orbit_position >= m_orbit.size()) m_current_orbit_position = 0;
    }

    m_orbit_time += fixed_frame_time;
}

void CelestialBody::Render(SDL_Renderer* renderer, float delta_time)
{
    if(m_body_points.size() > 0)
    {
        // SDL_SetRenderDrawColor(renderer, Colour::Yellow.r, Colour::Yellow.g, Colour::Yellow.b, Colour::Yellow.a);
        SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
        int cx{static_cast<int>(m_transform.PositionX() + m_parent->AjustedPosition().X())};//centre x offset
        int cy{static_cast<int>(m_transform.PositionY() + m_parent->AjustedPosition().Y())};//centre y offset

        //adds orbit
        if(m_orbit.size() > 0)
        {
            // cx += m_orbit[m_current_orbit_position].X();
            // cy += m_orbit[m_current_orbit_position].Y();

            int next_index = m_current_orbit_position + 1;
            if((unsigned)next_index >= m_orbit.size()) next_index = 0;

            float t = m_orbit_time / m_orbit_wait_time;

            cx += m_orbit[m_current_orbit_position].X() + (m_orbit[next_index].X() - m_orbit[m_current_orbit_position].X() ) * t;
            cy += m_orbit[m_current_orbit_position].Y() + (m_orbit[next_index].Y() - m_orbit[m_current_orbit_position].Y() ) * t;
        }

        for(auto point : m_body_points)
        {
            int x{point.x};
            int y{point.y};

            // int cx{static_cast<int>(m_position.X())};//centre x offset
            // int cy{static_cast<int>(m_position.Y())};//centre y offset

            SDL_RenderDrawPoint(renderer, x + cx, y + cy);//O1
            SDL_RenderDrawPoint(renderer, y + cx, x + cy);//O2

            SDL_RenderDrawPoint(renderer, -y + cx, x + cy);//O3
            SDL_RenderDrawPoint(renderer, -x + cx, y + cy);//O4

            SDL_RenderDrawPoint(renderer, -x + cx, -y + cy);//O5
            SDL_RenderDrawPoint(renderer, -y + cx, -x + cy);//O6

            SDL_RenderDrawPoint(renderer, y + cx, -x + cy);//O7
            SDL_RenderDrawPoint(renderer, x + cx, -y + cy);//O8
        }
    }
}

void CelestialBody::RenderOrbit(SDL_Renderer *renderer)
{
    int cx{static_cast<int>(m_transform.PositionX() + m_parent->AjustedPosition().X())};//centre x offset
    int cy{static_cast<int>(m_transform.PositionY() + m_parent->AjustedPosition().Y())};//centre y offset

    for(auto v:m_orbit)
        SDL_RenderDrawPoint(renderer, (int)v.X()+cx, (int)v.Y()+cy);
}

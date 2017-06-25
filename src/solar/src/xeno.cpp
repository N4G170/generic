#include "xeno.hpp"
#include "constants.hpp"

Xeno::Xeno():CelestialBody(), m_rotation_sin{static_cast<float>(sin(xeno_orbit_rotation_angle))}, m_rotation_cos{static_cast<float>(cos(xeno_orbit_rotation_angle))}
{

}

void Xeno::Move(float fixed_frame_time)
{
    if(m_orbit_time > m_orbit_wait_time)
    {
        m_orbit_time = 0;
        ++m_current_orbit_position;
        if(m_current_orbit_position >= m_orbit.size()) m_current_orbit_position = 0;
    }

    for(unsigned int i{0}; i<m_orbit.size();++i)
    {
        //the m_transform.Position().Y() holds the offset that the ellipse has

        float x = m_orbit[i].X() * m_rotation_cos + (m_orbit[i].Y() + m_transform.Position().Y()) * m_rotation_sin;
        float y = (m_orbit[i].Y() + m_transform.Position().Y()) * m_rotation_cos - m_orbit[i].X() * m_rotation_sin - m_transform.Position().Y();
        m_orbit[i].X( x );
        m_orbit[i].Y( y );
        // m_orbit[i].X( m_orbit[i].X() + cos(1.5));
        // m_orbit[i].Y( m_orbit[i].Y() + sin(1.5));
    }

    m_orbit_time += fixed_frame_time;
}

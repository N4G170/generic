#include "orbits.hpp"
#include "constants.hpp"
#include <cmath>

void GenerateOrbit(std::vector<Vector2<float>>& orbit_storage, float perihelion, float aphelion, float rad_angle_jump)
{
    orbit_storage.clear();
    float double_pi{(Math::PI * 2)};

    for(float angle{0}; angle <= double_pi; angle += rad_angle_jump)//in rad (1º = 0.017rad)
    {
        //parametric form
        // x = a + radius * cos(t); with a being centre x and t the angle between 0 and 2PI
        // y = b + radius * sin(t); with a being centre y and t the angle between 0 and 2PI
        orbit_storage.push_back( {aphelion * cos(angle), perihelion * sin(angle)} );
    }
}

void GenerateMercuryOrbit(std::vector<Vector2<float>>& orbit_storage)
{
    orbit_storage.clear();

    float perihelion{(sun_radius + sun_radius/2)};
    float aphelion{(perihelion * 1.517f)};
    float double_pi{(Math::PI * 2)};

    for(float angle{0}; angle <= double_pi; angle += 0.01)
    {
        //parametric form
        // x = a + radius * cos(t); with a being centre x and t the angle between 0 and 2PI
        // y = b + radius * sin(t); with a being centre y and t the angle between 0 and 2PI
        orbit_storage.push_back( {aphelion * cos(angle), perihelion * sin(angle)} );
    }
}

void GenerateVenusOrbit(std::vector<Vector2<float>>& orbit_storage)
{
    orbit_storage.clear();

    float perihelion{(2 * (sun_radius + sun_radius/2))};
    float aphelion{(perihelion * 1.0136f)};
    float double_pi{(Math::PI * 2)};

    for(float angle{0}; angle <= double_pi; angle += 0.01)
    {
        //parametric form
        // x = a + radius * cos(t); with a being centre x and t the angle between 0 and 2PI
        // y = b + radius * sin(t); with a being centre y and t the angle between 0 and 2PI
        orbit_storage.push_back( {aphelion * cos(angle), perihelion * sin(angle)} );
    }
}

#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP

#include "object.hpp"
#include "enums.hpp"
#include <vector>
#include <SDL2/SDL.h>

class CelestialBody : public Object
{
    public:
        CelestialBody();
        ~CelestialBody();

        void Configure(CelestialBodies type, CelestialBody* parent);

        virtual void Move(float fixed_frame_time);
        virtual void Render(SDL_Renderer* renderer, float delta_time);
        virtual void RenderOrbit(SDL_Renderer* renderer);

        Vector2<float> AjustedPosition();
    protected:
        std::vector<SDL_Point> m_body_points;
        SDL_Colour m_colour;
        CelestialBody* m_parent;
        float m_radius;

        //orbit
        std::vector<Vector2<float>> m_orbit;
        int m_current_orbit_position;
        float m_orbit_time;
        float m_orbit_wait_time;
};

#endif //CELESTIAL_BODY_HPP

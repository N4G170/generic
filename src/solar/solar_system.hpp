#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include "state_interface.hpp"
#include "vector2.hpp"
#include "sdl_gui_label.hpp"

#include "celestial_body.hpp"
#include "xeno.hpp"
#include "space_rock.hpp"


class SolarSystem : public StateInterface
{
    public:
        SolarSystem(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr);
        virtual ~SolarSystem();

        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&);

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float delta_time = 1);

        /**
         * \brief Render the state visual elements
         */
        virtual void Render(SDL_Renderer*, float delta_time);

    private:
        std::vector<sdl_gui::Label*> m_labels;
        std::vector<Vector2<int>> m_background_stars;
        bool m_show_orbit;
        bool m_pause;

        CelestialBody m_system_center;
        CelestialBody m_sun;
        CelestialBody m_sun_twin;
        CelestialBody m_mercury;
        CelestialBody m_venus;
        CelestialBody m_terra;
        CelestialBody m_luna;
        Xeno m_xeno;

        std::vector<SpaceRock> m_space_rocks;
        std::vector<CelestialBodies*> m_all_bodies;
};

#endif //SOLAR_SYSTEM_HPP

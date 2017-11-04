#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP

#include <vector>
#include <unordered_map>
#include "state_interface.hpp"
#include "vector3.hpp"

#include "enums.hpp"
#include "object.hpp"
#include "planet.hpp"
#include "comet.hpp"
#include "resource_manager.hpp"


class SolarSystem : public StateInterface
{
    public:
        SolarSystem(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);
        virtual ~SolarSystem() noexcept;

        /**
         * \brief Precess SDL user input
         */
        void Input(const SDL_Event&) override;

        /**
         * \brief Process any logic, runs after input
         */
        void Logic(float delta_time = 1) override;

        /**
         * \brief Process any logic, runs after input
         */
        void FixedLogic(float fixed_delta_time = 1) override;

        /**
         * \brief Render the state visual elements
         */
        void Render(SDL_Renderer*, float delta_time) override;

        void Enter() override;
        void Exit() override;

    private:
        std::vector<Planet*> m_planets;
        std::vector<Comet*> m_comets;

        bool m_show_orbit;
        bool m_pause;
};

#endif //SOLAR_SYSTEM_HPP

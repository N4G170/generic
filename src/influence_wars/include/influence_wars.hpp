#ifndef INFLUENCE_WARS_HPP
#define INFLUENCE_WARS_HPP

#include <vector>
#include "state_interface.hpp"
#include "influence_cell.hpp"

class InfluenceWars : public  StateInterface
{
    public:
        InfluenceWars(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);
        virtual ~InfluenceWars() noexcept;
        // InfluenceWars(const InfluenceWars& other);
        // InfluenceWars(InfluenceWars&& other) noexcept;

        InfluenceWars& operator= (const InfluenceWars& other);
        InfluenceWars& operator= (InfluenceWars&& other) noexcept;

        /**
         * \brief Precess SDL user input
         */
        void Input(const SDL_Event&) override;

        /**
         * \brief Process any logic, runs after input
         */
        void Logic(float delta_time = 1) override;

        void FixedLogic(float fixed_delta_time) override {}

        /**
         * \brief Render the state visual elements
         */
        void Render(SDL_Renderer*, float delta_time) override;

        void Enter() override;
        void Exit() override;

    private:
        std::vector<InfluenceCell> m_map;

};

#endif //INFLUENCE_WARS_HPP

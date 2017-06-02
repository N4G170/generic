#ifndef INFLUENCE_WARS_HPP
#define INFLUENCE_WARS_HPP

#include <vector>
#include "state_interface.hpp"
#include "influence_cell.hpp"

class InfluenceWars : public  StateInterface
{
    public:
        InfluenceWars(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr);
        virtual ~InfluenceWars() noexcept;
        // InfluenceWars(const InfluenceWars& other);
        // InfluenceWars(InfluenceWars&& other) noexcept;

        InfluenceWars& operator= (const InfluenceWars& other);
        InfluenceWars& operator= (InfluenceWars&& other) noexcept;

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
        std::vector<InfluenceCell> m_map;

};

#endif //INFLUENCE_WARS_HPP

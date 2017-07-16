#ifndef PARTICLE_STATE_HPP
#define PARTICLE_STATE_HPP

#include <vector>
#include <utility>
#include "constants.hpp"
#include "state_interface.hpp"

class ParticleState : public StateInterface
{
    public:
        //<f> Constructors & operator=
        ParticleState(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr);
        virtual ~ParticleState();

        ParticleState(const ParticleState& other);
        ParticleState(ParticleState&& other);

        ParticleState& operator= (const ParticleState& other);
        ParticleState& operator= (ParticleState&& other);

        //</f>

        //<f> Interface
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
        //</f>
    private:

};

#endif//PARTICLE_STATE_HPP

#ifndef PARTICLE_STATE_HPP
#define PARTICLE_STATE_HPP

#include "state_interface.hpp"
#include "particle_emitter.hpp"

class ParticleState : public StateInterface
{
    public:
        //<f> Constructors & operator=
        ParticleState(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);
        virtual ~ParticleState() noexcept;

        ParticleState(const ParticleState& other);
        ParticleState(ParticleState&& other) noexcept;

        ParticleState& operator= (const ParticleState& other);
        ParticleState& operator= (ParticleState&& other) noexcept;

        //</f>

        //<f> Interface
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
        //</f>

        void BackToMenuCallback();
    private:
        ParticleEmitter* m_emitter;
};

#endif//PARTICLE_STATE_HPP

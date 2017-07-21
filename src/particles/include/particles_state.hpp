#ifndef PARTICLE_STATE_HPP
#define PARTICLE_STATE_HPP

#include "state_interface.hpp"
#include "sdl_gui_manager.hpp"

class ParticleState : public StateInterface
{
    public:
        //<f> Constructors & operator=
        ParticleState(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr);
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

        void BackToMenuCallback();
    private:

        sdl_gui::GuiManager m_gui_manager;

};

#endif//PARTICLE_STATE_HPP

#ifndef BASICINTERFACE_HPP
#define BASICINTERFACE_HPP
#include <memory>
#include <SDL2/SDL.h>

#include "state_machine.hpp"

class StateMachine;
struct MainFlags;

/**
 * \brief Basic Interface to be used by the main state machine
 */
class StateInterface
{
    public:
        StateInterface(StateMachine* state_machine, const std::string& state_name):m_state_machine_ptr{state_machine},
        m_state_name{state_name} {};
        virtual ~StateInterface(){ m_state_machine_ptr = nullptr; };

        // StateInterface(const StateInterface& other):m_state_machine_ptr{other.m_state_machine_ptr},
        // m_state_name{other.m_state_name} {};

        // StateInterface(const StateInterface&& other)
        // {
        //     m_state_machine_ptr = std::move(other.m_state_machine_ptr);
        //     m_state_name = std::move(other.m_state_name);
        // };

        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&) = 0;

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float delta_time = 1) = 0;

        /**
         * \brief Render the state visual elements
         */
        virtual void Render(SDL_Renderer*, float delta_time) = 0;

        /**
         * \brief Not yet in use
         */
        virtual void Enter(){};

        /**
         * \brief Not yet in use
         */
        virtual void Exit(){};

        std::string Name() const { return m_state_name; }

    protected:
        StateMachine* m_state_machine_ptr;
    private:
        std::string m_state_name;
};

#endif // BASICINTERFACE_HPP

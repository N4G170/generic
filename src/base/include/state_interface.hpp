#ifndef BASICINTERFACE_HPP
#define BASICINTERFACE_HPP
#include <memory>
#include "SDL.h"

#include "state_machine.hpp"
#include "system_manager.hpp"

class StateMachine;
struct MainFlags;

/**
 * \brief Basic Interface to be used by the main state machine
 */
class StateInterface
{
    public:
        //<f> Constructors & operator=
        StateInterface(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):m_state_machine_ptr{state_machine},
        m_system_manager_ptr{system_manager_ptr}, m_state_name{state_name} {};

        virtual ~StateInterface(){ m_state_machine_ptr = nullptr; m_system_manager_ptr = nullptr; };

        StateInterface(const StateInterface& other) : m_state_machine_ptr{other.m_state_machine_ptr}, m_system_manager_ptr{other.m_system_manager_ptr},
            m_state_name{other.m_state_name} {};

        StateInterface(StateInterface&& other) : m_state_machine_ptr{std::move(other.m_state_machine_ptr)}, m_system_manager_ptr{std::move(other.m_system_manager_ptr)},
            m_state_name{std::move(other.m_state_name)} {};

        StateInterface& operator= (const StateInterface& other)
        {
            if(this != &other)
            {
                m_state_machine_ptr = other.m_state_machine_ptr;
                m_system_manager_ptr = other.m_system_manager_ptr;
                m_state_name = other.m_state_name;
            }
            return *this;
        }
        StateInterface& operator= (const StateInterface&& other)
        {
            if(this != &other)
            {
                m_state_machine_ptr = std::move(other.m_state_machine_ptr);
                m_system_manager_ptr = std::move(other.m_system_manager_ptr);
                m_state_name = std::move(other.m_state_name);
            }
            return *this;
        }
        //</f>

        //<f> Interface
        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&) = 0;

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float delta_time = 1) = 0;

        virtual void FixedLogic(float fixed_delta_time = 1) = 0;

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
        //</f>

        //<f> Getters/Setters
        std::string Name() const { return m_state_name; }
        //</f>

    protected:
        StateMachine* m_state_machine_ptr;
        SystemManager* m_system_manager_ptr;
    private:
        std::string m_state_name;
};

#endif // BASICINTERFACE_HPP

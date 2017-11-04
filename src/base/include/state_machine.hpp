#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include <string>
#include "SDL.h"
#include "system_manager.hpp"

#include "state_interface.hpp"
//class ResourceManager;
class StateInterface;

/**
 * \brief Basic state machine
 */
class StateMachine
{
    public:
        StateMachine(SystemManager* system_manager_ptr, bool* quit_flag);
        virtual ~StateMachine();

        /**
         * \brief Sets next state
         * \details Receives a string with the name for the next state. (Might change it to an enumerate)
         */
        void ChangeState(const std::string& state);
        /**
         * \brief Returns the machine to its previous state (Not yet in use)
         */
        void ReturnToPreviousState();

        /**
         * \brief Calls Input for current state
         */
        void Input(const SDL_Event&);

        /**
         * \brief Calls Logic for current state
         */
        void Logic(float delta_time);

        /**
         * \brief Calls Logic for current state
         */
        void FixedLogic(float fixed_delta_time);

        /**
         * \brief Calls Render for current state. The renderer is passed with the resource manager
         */
        void Render(float delta_time);

        bool* m_quit_flag;
    protected:
    private:
        /**
         * \brief Just a shortcut for the resource manager owned renderer
         */
        SystemManager* m_system_manager_ptr;

        std::unique_ptr<StateInterface> m_current_state;
        std::unique_ptr<StateInterface> m_previous_state;
};

#endif // STATEMACHINE_HPP

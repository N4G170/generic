#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <memory>
#include "state_interface.hpp"

class Menu : public StateInterface
{
    public:
        Menu(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);

        virtual ~Menu();
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
        void ChangeStateCallback(const std::string& state);
};
#endif //MENU_HPP

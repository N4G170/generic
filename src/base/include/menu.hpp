#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <memory>
#include "state_interface.hpp"
#include "sdl_gui_manager.hpp"

class Menu : public StateInterface
{
    public:
        Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr);

        virtual ~Menu();
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

        virtual void Enter();
        virtual void Exit();

    private:
        sdl_gui::GuiManager m_gui_manager;

        void ChangeStateCallback(const std::string& state);
};
#endif //MENU_HPP

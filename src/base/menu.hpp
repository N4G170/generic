#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include "state_interface.hpp"
#include "button.hpp"

class Menu : public StateInterface
{
    public:
        Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, TTF_Font* font);

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

    private:
        std::vector<sdl_gui::Button*> m_buttons;
};
#endif //MENU_HPP

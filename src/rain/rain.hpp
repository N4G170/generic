#ifndef RAIN_HPP
#define RAIN_HPP

#include <vector>
#include <SDL2/SDL_mixer.h>

#include "state_interface.hpp"
#include "drop.hpp"
#include "constants.hpp"

class Rain : public StateInterface
{
    public:
        Rain(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr);

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
        void PlayDropSound();
        std::vector<Drop> m_drops;
        SDL_Colour m_bg_colour;

        Mix_Chunk* m_drop_sound;
        bool m_mute;
};

#endif //RAIN_HPP

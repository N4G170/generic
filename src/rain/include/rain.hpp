#ifndef RAIN_HPP
#define RAIN_HPP

#include <vector>
#include "SDL_mixer.h"

#include "state_interface.hpp"
#include "drop.hpp"
#include "object_manager.hpp"
#include "collision_manager.hpp"
#include "constants.hpp"

class Rain : public StateInterface
{
    public:
        Rain(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);

        /**
         * \brief Precess SDL user input
         */
        void Input(const SDL_Event&) override;

        /**
         * \brief Process any logic, runs after input
         */
        void Logic(float delta_time = 1) override;

        void FixedLogic(float fixed_delta_time) override;
        /**
         * \brief Render the state visual elements
         */
        void Render(SDL_Renderer*, float delta_time) override;

        void Enter() override;
        void Exit() override;

    private:
        void PlayDropSound();
        Mix_Chunk* m_drop_sound;
        bool m_mute;

        std::vector<Drop*> m_drops;
        Vector3<float> m_wind;
        float m_wind_duration;
        float m_current_wind_duration;

        Object* m_mask;
};

#endif //RAIN_HPP

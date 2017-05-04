#include "rain.hpp"
#include <iostream>

Rain::Rain(StateMachine* state_machine, const std::string& state_name):StateInterface(state_machine, state_name)
{
    m_bg_colour = Colour::Storm_Petrel;
    m_drop_sound = Mix_LoadWAV("data/sfx/drop.wav");
    m_mute = true;

    for(int i{0}; i < drop_count; ++i)
    {
        m_drops.push_back(Drop{ std::bind(&Rain::PlayDropSound, this) });
    }
}

void Rain::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
            case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            case SDLK_m: m_mute = !m_mute; if(m_mute) Mix_Volume(1, 0); else Mix_Volume(1, MIX_MAX_VOLUME); break;
            // case SDLK_f:
            // fullscreen = !fullscreen;
            //
            // if(fullscreen)
            //     SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
            // else
            //     SDL_SetWindowFullscreen(window.get(), 0);
            // break;
        }
    }
}

void Rain::Logic(float delta_time)
{
    //Logic and Render being called in separate moments causes the repetition os the loop
    for(Drop& d : m_drops)
    {
        d.Logic(delta_time);
    }
}

void Rain::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_SetRenderDrawColor( renderer, m_bg_colour.r, m_bg_colour.g, m_bg_colour.b, m_bg_colour.a );
    SDL_RenderClear( renderer );

    for(Drop& d : m_drops)
    {
        d.Render(renderer, delta_time);
    }
}

void Rain::PlayDropSound()
{
    if(m_mute)
        return;
    // Mix_PlayChannel(-1, m_drop_sound, 0);
    Mix_FadeInChannel(-1, m_drop_sound, 0, 150);
}

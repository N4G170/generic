#include "state_machine.hpp"
#include "constants.hpp"
#include "rain.hpp"
#include "menu.hpp"
#include "snake_game.hpp"
#include "solar_system.hpp"
#include "map_demo.hpp"
#include "influence_wars.hpp"
#include <iostream>

StateMachine::StateMachine(SDL_Renderer* renderer, TTF_Font* font, bool* quit_flag)
{
    m_previous_state.reset(nullptr);
    m_current_state.reset(nullptr);

    m_renderer_ptr = renderer;
    m_quit_flag = quit_flag;
    m_font = font;
}

StateMachine::~StateMachine()
{
    m_previous_state.reset(nullptr);
    m_current_state.reset(nullptr);

    m_renderer_ptr = nullptr;
}

/**
 * \brief Sets next state
 * \details Receives a string with the name for the next state. (Might change it to an enumerate)
 */
void StateMachine::ChangeState(const std::string& state)
{
    if(m_current_state && m_current_state->Name() == state)
        return;

    if(m_previous_state && m_previous_state->Name() == state)//revert to previous state
    {
        m_current_state.swap(m_previous_state);
        return;
    }
    else //if(m_current_state && !m_previous_state)//store previous state
    {
        m_previous_state.reset(m_current_state.release());
    }

    //select next state
    if(state == StateName::Menu)
    {
        m_current_state.reset(new Menu(this, StateName::Menu, m_renderer_ptr, m_font));
    }
    else if(state == StateName::Rain)
    {
        m_current_state.reset(new Rain(this, StateName::Rain));
    }
    else if(state == StateName::Snake)
    {
        m_current_state.reset(new SnakeGame(this, StateName::Snake, m_renderer_ptr, m_font));
    }
    else if(state == StateName::Solar_System)
    {
        m_current_state.reset(new SolarSystem(this, StateName::Solar_System, m_renderer_ptr, m_font));
    }
    else if(state == StateName::Map_Demo)
    {
        m_current_state.reset(new MapDemo(this, StateName::Map_Demo, m_renderer_ptr, m_font));
    }
    else if(state == StateName::Influence_Wars)
    {
        m_current_state.reset(new InfluenceWars(this, StateName::Influence_Wars, m_renderer_ptr, m_font));
    }
}

/**
 * \brief Calls Input for current state
 */
void StateMachine::Input(const SDL_Event& event)
{
    if(m_current_state)
        m_current_state->Input(event);
}

/**
 * \brief Calls Logic for current state
 */
void StateMachine::Logic(float delta_time)
{
    if(m_current_state)
        m_current_state->Logic(delta_time);
}

/**
 * \brief Calls Render for current state
 */
void StateMachine::Render(float delta_time)
{
    if(m_current_state)
        m_current_state->Render(m_renderer_ptr, delta_time);
}

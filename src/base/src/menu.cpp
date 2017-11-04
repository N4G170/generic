#include "menu.hpp"
#include "constants.hpp"
#include <iostream>

SDL_Colour bg{12,34,56,255};

Menu::Menu(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr)
{
    std::cout<<"<b>1</b> - A* Grid Map"<<std::endl;
    std::cout<<"<b>2</b> - Rain demo"<<std::endl;
    std::cout<<"<b>3</b> - Snake Game demo"<<std::endl;
    std::cout<<"<b>4</b> - Solar System demo"<<std::endl;
    std::cout<<"<b>5</b> - Influence Wars"<<std::endl;
    std::cout<<"<b>6</b> - Particles"<<std::endl;
}

Menu::~Menu()
{

}

void Menu::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: *m_state_machine_ptr->m_quit_flag = true; break;
            case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Map_Demo); break;
            case SDLK_2: m_state_machine_ptr->ChangeState(StateName::Rain); break;
            case SDLK_3: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            case SDLK_4: m_state_machine_ptr->ChangeState(StateName::Solar_System); break;
            case SDLK_5: m_state_machine_ptr->ChangeState(StateName::Influence_Wars); break;
            case SDLK_6: m_state_machine_ptr->ChangeState(StateName::Particles); break;
        }
    }
}

bool u{false};
float t{0};

void Menu::Logic(float delta_time)
{

}

void Menu::Render(SDL_Renderer* renderer, float delta_time)
{
    // SDL_SetRenderDrawColor( renderer, Colour::Grey.r, Colour::Grey.g, Colour::Grey.b, Colour::Grey.a );
    SDL_SetRenderDrawColor( renderer, bg.r, bg.g, bg.b, bg.a );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, Colour::Storm_Petrel.r, Colour::Storm_Petrel.g, Colour::Storm_Petrel.b, 128);
    // SDL_SetRenderDrawColor( renderer, 128,255,255,255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect aux_rect{10,10,200,100};
    SDL_RenderFillRect(renderer, &aux_rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

void Menu::Enter()
{

}

void Menu::Exit()
{

}

void Menu::ChangeStateCallback(const std::string &state)
{
    m_state_machine_ptr->ChangeState(state);
}

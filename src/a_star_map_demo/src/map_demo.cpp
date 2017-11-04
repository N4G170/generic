#include "map_demo.hpp"
#include "constants.hpp"
#include <functional>
#include "utils.hpp"
#include "message_writer.hpp"
#include "image.hpp"

MapDemo::MapDemo(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr), m_mouse_inside_viewport{false},
m_map_width{0}, m_map_height{0}, m_scale{1}, m_mouse_hover_cell_index{-1}, m_selected_cell_index{-1}, m_army_selected{false}
{

}

MapDemo::~MapDemo()
{

}

void MapDemo::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
        }
    }
}

void MapDemo::Logic(float fixed_frame_time)
{

}

void MapDemo::Render(SDL_Renderer* renderer, float delta_time)
{

}

void MapDemo::Enter()
{
    auto map_obj{m_system_manager_ptr->Objects()->CreateObject()};
    auto m_map_script{ new Map{m_system_manager_ptr}};
    map_obj->AddScript(m_map_script);
    m_map_script->BuildMap();
}
void MapDemo::Exit()
{
    m_system_manager_ptr->Clear();
}

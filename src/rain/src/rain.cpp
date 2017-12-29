#include "rain.hpp"
#include <iostream>
#include "object.hpp"
#include "image.hpp"
#include "constants.hpp"
#include "collider.hpp"
#include "utils.hpp"
#include "basic_frame_animation.hpp"
#include "mask.hpp"
#include "light.hpp"
#include "random.hpp"

Rain::Rain(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr) { }

void Rain::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
            case SDLK_m: m_mute = !m_mute; if(m_mute) Mix_Volume(1, 0); else Mix_Volume(1, MIX_MAX_VOLUME); break;
            case SDLK_s: m_mask->Enabled( !m_mask->Enabled() ); break;
        }
    }
}

void Rain::FixedLogic(float fixed_delta_time) { }

void Rain::Logic(float delta_time)
{
    m_current_wind_duration += delta_time;

    if(m_current_wind_duration >= m_wind_duration)//calculate new wind force
    {
        m_current_wind_duration = 0;

        float wind_x{Random( -c_max_wind_x_force, c_max_wind_x_force )};
        float wind_y{Random( 0.f, 30.f )};
        // float wind_z{Random( -1.f, 1.f ) };

        m_wind = {wind_x, wind_y, 0};

        //new wind duration
        m_wind_duration = Random(3.f, 10.f);
    }

    for(auto & drop : m_drops)
        drop->ChangeWindForce(m_wind);
}

void Rain::Render(SDL_Renderer* renderer, float delta_time) { }

void Rain::Enter()
{
    //BG
    auto bg_object{m_system_manager_ptr->Objects()->CreateObject()};
    bg_object->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 0});
    bg_object->TransformPtr()->LocalScale({static_cast<float>(window_width), static_cast<float>(window_height), 0});
    auto bg_image{ new Image(m_system_manager_ptr) };
    bg_image->ColourModulation(Colour::Storm_Petrel);
    bg_object->AddScript(bg_image);
    bg_object->TransformPtr()->LocalPositionZ(500);

    //floor Collider
    // auto floor_object{m_system_manager_ptr->Objects()->CreateObject()};
    // floor_object->AddScript( new Collider() );
    // floor_object->TransformPtr()->LocalScale({window_width, 300, 1});
    // floor_object->TransformPtr()->LocalPosition({0, window_height, 0});
    // floor_object->AddTag("floor");
    // auto floor_collider{new Collider()};
    // floor_object->AddScript(floor_collider);
    // m_system_manager_ptr->Colliders()->AddCollider(floor_collider);

    //create drops
    for(auto i{0}; i<drop_count; ++i)
    {
        auto drop{m_system_manager_ptr->Objects()->CreateObject()};
        auto drop_image{new Image(m_system_manager_ptr)};
        drop->AddScript(drop_image);

        auto drop_script{new Drop(m_system_manager_ptr)};
        drop->AddScript(drop_script);

        // auto drop_collider{new Collider()};
        // drop->AddScript(drop_collider);
        // drop_collider->OnCollision = std::bind(&Drop::DropHit, drop_script, std::placeholders::_1);
        // m_system_manager_ptr->Colliders()->AddCollider(drop_collider);

        drop_script->ResetDrop();
        m_drops.push_back(drop_script);
    }

    m_drop_sound = Mix_LoadWAV("data/sfx/drop.wav");
    m_mute = true;


    m_mask = m_system_manager_ptr->Objects()->CreateObject();
    auto mask_script{new Mask{m_system_manager_ptr}};
    m_mask->AddScript(mask_script);
    m_mask->TransformPtr()->LocalPosition({50,50,-1});

    //mask image decal
    auto mask_image{new Image{m_system_manager_ptr}};
    m_mask->AddScript(mask_image);
    mask_image->SetImage("data/img/light.png");
    m_mask->TransformPtr()->LocalScale({700,700,1});
    mask_script->SetImage(mask_image);
    mask_image->Disable();

    auto light_script{new Light{}};
    m_mask->AddScript(light_script);

    SDL_WarpMouseInWindow(m_system_manager_ptr->Window(), (int)(window_centre_x), (int)(window_centre_y));

    auto menu_obj{m_system_manager_ptr->Objects()->CreateObject()};
    auto menu_image{ new Image{m_system_manager_ptr} };
    menu_image->SetImage("data/img/rain_menu.png");
    menu_obj->AddScript(menu_image);
    menu_obj->TransformPtr()->LocalScale({300,100,0});
    menu_obj->TransformPtr()->LocalPosition({155,55,-2});
}

void Rain::Exit()
{
    m_system_manager_ptr->Clear();
}

void Rain::PlayDropSound()
{
    if(m_mute)
        return;
    // Mix_PlayChannel(-1, m_drop_sound, 0);
    Mix_FadeInChannel(-1, m_drop_sound, 0, 150);
}

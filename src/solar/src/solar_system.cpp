#include "solar_system.hpp"
#include "constants.hpp"
#include "random.hpp"
#include "utils.hpp"
#include "image.hpp"
#include "background_stars.hpp"
#include "planet.hpp"
#include "comet.hpp"
#include "collider.hpp"
#include "debug_render.hpp"
#include <iostream>

std::vector<Collider*> planet_colliders{};

SolarSystem::SolarSystem(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr), m_show_orbit{true}, m_pause{false}
{

}

SolarSystem::~SolarSystem() noexcept
{

}


void SolarSystem::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
            case SDLK_s: m_show_orbit = ! m_show_orbit; break;
            case SDLK_p: m_pause = ! m_pause; break;
        }
    }
}

void SolarSystem::Logic(float delta_time)
{
    if(m_pause) return;

    m_system_manager_ptr->Objects()->Logic(delta_time);

    //check for gravity influence
    for(auto comet : m_comets)
    {
        //check every planet/star
        for(auto planet : m_planets)
        {
            auto distance_vector = planet->Owner()->TransformPtr()->GlobalPosition() - comet->Owner()->TransformPtr()->GlobalPosition();
            auto distance_squared = distance_vector.LengthSquared();

            //influence
            if(distance_squared > 0)
            {
                auto influence = planet->Mass() / distance_squared;
                distance_vector.Normalize();
                distance_vector *= influence;

                //apply influence
                comet->InfluenceDirection(distance_vector);
                comet->Accelerate(influence);
            }
        }
    }
}

void SolarSystem::FixedLogic(float fixed_delta_time)
{
    // m_system_manager_ptr->Objects()->FixedLogic(fixed_delta_time);
    // m_system_manager_ptr->Colliders()->FixedLogic(fixed_delta_time);
}

void SolarSystem::Render(SDL_Renderer* renderer, float delta_time)
{
    // auto bounds{m_system_manager_ptr->MainCamera()->CameraBounds()};
    // SDL_Rect dst{BoundsToSDLRect(bounds)};
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderDrawRect(renderer, &dst);
}

void SolarSystem::Enter()
{
    auto menu_obj{m_system_manager_ptr->Objects()->CreateObject()};
    auto menu_image{ new Image{m_system_manager_ptr} };
    menu_image->SetImage("data/img/back_to_main.png");
    menu_obj->AddScript(menu_image);
    menu_obj->TransformPtr()->LocalScale({300,100,0});
    menu_obj->TransformPtr()->LocalPosition({155,55,0});

    //<f> Background Image
    auto bg_obj{m_system_manager_ptr->Objects()->CreateObject()};
    auto bg_image{ new Image{m_system_manager_ptr} };
    bg_obj->AddScript(bg_image);
    bg_obj->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 10});
    bg_obj->TransformPtr()->LocalScale({static_cast<float>(window_width), static_cast<float>(window_height), 0});
    bg_image->ColourModulation({0,0,0,255});
    //</f> /Background Image

    //<f> generate random backgroud stars
    int total_stars = Random(500,750);

    auto window_diagonal{ static_cast<float>(std::sqrt(window_width * window_width + window_height * window_height)) };
    for(auto i{0}; i<total_stars; ++i)
    {
        auto obj{m_system_manager_ptr->Objects()->CreateObject()};
        auto star_image{ new Image{m_system_manager_ptr} };
        obj->AddScript(star_image);

        auto x{Random(-5.f, window_diagonal + 5.f)};
        auto y{Random(-5.f, window_diagonal + 5.f)};
        obj->TransformPtr()->LocalPosition({x,y,0.f});

        auto star_script{ new BackgroundStars()};
        obj->AddScript(star_script);

        //move speed
        star_script->UpdateInterval( Random(0.01, 0.1) );
        star_script->RotationAngle( Random(-0.01, 0.01) );
    }
    //</f> / generate random backgroud stars

    //<f> Create Planets
    auto system_centre{m_system_manager_ptr->Objects()->CreateObject()};
    system_centre->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 0});

    //<f> Orbit render lambda
    auto ConfigOrbitRender = [&](Planet* owner_planet, Transform* parent, const SDL_Colour& orbit_colour)
    {
        //orbit render
        auto orbit_object{m_system_manager_ptr->Objects()->CreateObject()};
        orbit_object->TransformPtr()->Parent(parent);
        orbit_object->TransformPtr()->LocalPosition({0, 0, 5});
        auto orbit_render{new OrbitRender{m_system_manager_ptr}};
        orbit_object->AddScript(orbit_render);
        orbit_render->OrbitColour(orbit_colour);

        owner_planet->SetOrbitRender(orbit_render);
        owner_planet->RecalculateOrbit();
    };
    //</f> /Orbit render lambda

    //<f> SUN
    auto sun{m_system_manager_ptr->Objects()->CreateObject()};
    sun->TransformPtr()->Parent(system_centre->TransformPtr());
    sun->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto sun_img{new Image(m_system_manager_ptr)};

    sun->AddScript(sun_img);
    sun_img->SetImage("data/img/circle.png");
    sun->TransformPtr()->LocalScale({sun_radius, sun_radius, 1});
    sun->TransformPtr()->LocalPosition({0, 0, 0});

    auto sun_orbit{new Planet()};
    sun->AddScript(sun_orbit);
    sun_orbit->Perihelion(250);
    sun_orbit->Aphelion(225);
    sun_orbit->OrbitUpdateInterval(0.01f);
    sun_orbit->AngleStep(0.01f);
    sun_orbit->Mass(sun_radius * 10);


    m_planets.push_back(sun_orbit);

    auto sun_collider{new Collider()};
    sun->AddScript(sun_collider);
    planet_colliders.push_back(sun_collider);
    m_system_manager_ptr->Colliders()->AddCollider(sun_collider);

    //orbit render
    ConfigOrbitRender(sun_orbit, system_centre->TransformPtr(), Colour::White);
    //</f> /SUN

    //<f> MERCURY
    auto mercury{m_system_manager_ptr->Objects()->CreateObject()};
    mercury->TransformPtr()->Parent(sun->TransformPtr());
    mercury->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto mercury_img{new Image(m_system_manager_ptr)};

    mercury->AddScript(mercury_img);
    mercury_img->SetImage("data/img/circle.png");
    mercury_img->ColourModulation(Colour::Grey);
    mercury->TransformPtr()->GlobalScale({mercury_radius, mercury_radius, 1});

    auto mercury_orbit{new Planet()};
    mercury->AddScript(mercury_orbit);
    mercury_orbit->Perihelion(sun_radius * 2);
    mercury_orbit->Aphelion( mercury_orbit->Perihelion() * 1.0136f );
    mercury_orbit->OrbitUpdateInterval(0.01f);
    mercury_orbit->Mass(mercury_radius * 10);
    mercury_orbit->RecalculateOrbit();

    auto mercury_collider{new Collider()};
    mercury->AddScript(mercury_collider);
    planet_colliders.push_back(mercury_collider);
    m_system_manager_ptr->Colliders()->AddCollider(mercury_collider);

    //orbit render
    ConfigOrbitRender(mercury_orbit, sun->TransformPtr(), Colour::Grey);
    //</f> /MERCURY

    //<f> VENUS
    auto venus{m_system_manager_ptr->Objects()->CreateObject()};
    venus->TransformPtr()->Parent(sun->TransformPtr());
    venus->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto venus_img{new Image(m_system_manager_ptr)};

    venus->AddScript(venus_img);
    venus_img->SetImage("data/img/circle.png");
    venus_img->ColourModulation(Colour::Venus_Yellow);
    venus->TransformPtr()->GlobalScale({venus_radius, venus_radius, 1});

    auto venus_orbit{new Planet()};
    venus->AddScript(venus_orbit);
    venus_orbit->Perihelion(sun_radius * 4);
    venus_orbit->Aphelion( venus_orbit->Perihelion() * 1.0136f );
    venus_orbit->OrbitUpdateInterval(0.01f);
    venus_orbit->Mass(venus_radius * 10);
    venus_orbit->RecalculateOrbit();

    auto venus_collider{new Collider()};
    venus->AddScript(venus_collider);
    planet_colliders.push_back(venus_collider);
    m_system_manager_ptr->Colliders()->AddCollider(venus_collider);

    //orbit render
    ConfigOrbitRender(venus_orbit, sun->TransformPtr(), Colour::Venus_Yellow);
    //</f> /VENUS

    //<f> TERRA
    auto terra{m_system_manager_ptr->Objects()->CreateObject()};
    terra->TransformPtr()->Parent(sun->TransformPtr());
    terra->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto terra_img{new Image(m_system_manager_ptr)};

    terra->AddScript(terra_img);
    terra_img->SetImage("data/img/circle.png");
    terra_img->ColourModulation(Colour::Light_Blue);
    terra->TransformPtr()->GlobalScale({terra_radius, terra_radius, 1});

    auto terra_orbit{new Planet()};
    terra->AddScript(terra_orbit);
    terra_orbit->Perihelion(sun_radius * 8);
    terra_orbit->Aphelion( terra_orbit->Perihelion() * 1.033f );
    // terra_orbit->OrbitUpdateInterval(0.611f);
    terra_orbit->OrbitUpdateInterval(0.01f);
    terra_orbit->AngleStep(-0.5f);
    terra_orbit->Mass(terra_radius * 10);
    terra_orbit->RecalculateOrbit();

    auto terra_collider{new Collider()};
    terra->AddScript(terra_collider);
    planet_colliders.push_back(terra_collider);
    m_system_manager_ptr->Colliders()->AddCollider(terra_collider);

    //orbit render
    ConfigOrbitRender(terra_orbit, sun->TransformPtr(), Colour::Light_Blue);
    //</f> /TERRA

    //<f> LUNA
    auto luna{m_system_manager_ptr->Objects()->CreateObject()};
    luna->TransformPtr()->Parent(terra->TransformPtr());
    luna->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto luna_img{new Image(m_system_manager_ptr)};

    luna->AddScript(luna_img);
    luna_img->SetImage("data/img/circle.png");
    luna_img->ColourModulation(Colour::Grey);
    luna->TransformPtr()->GlobalScale({luna_radius, luna_radius, 1});

    auto luna_orbit{new Planet()};
    luna->AddScript(luna_orbit);
    luna_orbit->Perihelion(terra_radius * 2);
    luna_orbit->Aphelion(luna_orbit->Perihelion() * 1.116f);
    luna_orbit->OrbitUpdateInterval(0.01f);
    luna_orbit->AngleStep(1.f);
    luna_orbit->Mass(luna_radius * 10);
    luna_orbit->RecalculateOrbit();

    auto luna_collider{new Collider()};
    luna->AddScript(luna_collider);
    planet_colliders.push_back(luna_collider);
    m_system_manager_ptr->Colliders()->AddCollider(luna_collider);

    //orbit render
    ConfigOrbitRender(luna_orbit, terra->TransformPtr(), Colour::Grey);
    //</f> /LUNA

    //<f> XENO
    auto xeno{m_system_manager_ptr->Objects()->CreateObject()};
    xeno->TransformPtr()->Parent(sun->TransformPtr());
    xeno->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto xeno_img{new Image(m_system_manager_ptr)};
    xeno->AddScript(xeno_img);
    xeno_img->SetImage("data/img/circle.png");
    xeno_img->ColourModulation(Colour::Red);
    xeno->TransformPtr()->GlobalScale({xeno_radius, xeno_radius, 1});

    auto xeno_orbit{new Planet()};
    xeno->AddScript(xeno_orbit);
    xeno_orbit->Perihelion(sun_radius * 10);
    xeno_orbit->Aphelion(sun_radius * 5);
    xeno_orbit->OrbitUpdateInterval(0.01f);
    xeno_orbit->AngleStep(0.8f);
    xeno_orbit->Mass(xeno_radius * 10);;
    xeno_orbit->RecalculateOrbit();

    auto xeno_collider{new Collider()};
    xeno->AddScript(xeno_collider);
    planet_colliders.push_back(xeno_collider);
    m_system_manager_ptr->Colliders()->AddCollider(xeno_collider);

    //orbit render
    ConfigOrbitRender(xeno_orbit, sun->TransformPtr(), Colour::Red);

    xeno_orbit->RotationStep(0.01);
    //</f> /XENO

    //<f> XENO2
    auto xeno2{m_system_manager_ptr->Objects()->CreateObject()};
    xeno2->TransformPtr()->Parent(sun->TransformPtr());
    xeno2->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto xeno2_img{new Image(m_system_manager_ptr)};
    xeno2->AddScript(xeno2_img);
    xeno2_img->SetImage("data/img/circle.png");
    xeno2_img->ColourModulation(Colour::Purple);
    xeno2->TransformPtr()->GlobalScale({xeno_radius*0.8f, xeno_radius*0.8f, 1});

    auto xeno2_orbit{new Planet()};
    xeno2->AddScript(xeno2_orbit);
    xeno2_orbit->Perihelion(sun_radius * 10);
    xeno2_orbit->Aphelion(sun_radius * 2);
    xeno2_orbit->OrbitUpdateInterval(0.01f);
    xeno2_orbit->AngleStep(0.8f);
    xeno2_orbit->Mass(xeno_radius * 10);;
    xeno2_orbit->RecalculateOrbit();

    auto xeno2_collider{new Collider()};
    xeno2->AddScript(xeno2_collider);
    planet_colliders.push_back(xeno2_collider);
    m_system_manager_ptr->Colliders()->AddCollider(xeno2_collider);

    //orbit render
    ConfigOrbitRender(xeno2_orbit, sun->TransformPtr(), Colour::Purple);

    xeno2_orbit->RotationStep(-0.1);
    xeno2_orbit->PositionOffset({0, sun_radius * 8, 0});
    //</f> /XENO2

    //</f> /Create Planets

    //<f> Asteroids

    for(int i{0}; i<5; ++i)
    {
        auto comet{m_system_manager_ptr->Objects()->CreateObject()};
        comet->TransformPtr()->Anchor(AnchorType::Centre_Centre);
        auto comet_img{new Image(m_system_manager_ptr)};
        comet->AddScript(comet_img);
        comet_img->SetImage("data/img/circle.png");
        comet_img->ColourModulation(Colour::White);
        comet->TransformPtr()->LocalScale({3, 3, 1});

        auto comet_script{new Comet()};
        comet->AddScript(comet_script);
        comet_script->Reset();

        m_comets.push_back(comet_script);

        auto comet_collider{new Collider()};
        comet->AddScript(comet_collider);
        planet_colliders.push_back(comet_collider);
        m_system_manager_ptr->Colliders()->AddCollider(comet_collider);

        comet_collider->OnCollision = std::bind(&Comet::OnCollision, comet_script, std::placeholders::_1);
    }
    //</f> /Asteroids
}
void SolarSystem::Exit()
{
    m_system_manager_ptr->Clear();
}

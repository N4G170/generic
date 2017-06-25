#include "solar_system.hpp"
#include "constants.hpp"
#include "random.hpp"

SolarSystem::SolarSystem(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr):
    StateInterface(state_machine, state_name, resource_manager_ptr), m_show_orbit{true}, m_pause{false}
{
    //generate random backgroud stars
    int total_stars = Random(50, 250);
    m_background_stars.resize(total_stars);

    for(unsigned int i{0}; i < m_background_stars.size(); ++i)
    {
        m_background_stars[i].X( Random(0, window_width) );
        m_background_stars[i].Y( Random(0, window_height) );
    }

    m_system_center.Configure(CelestialBodies::NONE, nullptr);
    m_sun.Configure(CelestialBodies::SUN, &m_system_center);
    m_sun_twin.Configure(CelestialBodies::SUN2, &m_system_center);
    m_mercury.Configure(CelestialBodies::MERCURY, &m_system_center);
    m_venus.Configure(CelestialBodies::VENUS, &m_system_center);
    m_terra.Configure(CelestialBodies::TERRA, &m_system_center);
    m_luna.Configure(CelestialBodies::LUNA, &m_terra);
    m_xeno.Configure(CelestialBodies::XENO, &m_system_center);

    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "'ESC' - Return to menu", Colour::Magenta, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "'S' - Show/Hide orbits", Colour::Magenta, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "'P' - PAuse Simulation", Colour::Magenta, 15, 15, -1, -1));

    int number_of_rocks{10};
    m_space_rocks.resize( number_of_rocks );

    for(int i{0}; i < number_of_rocks; ++i)
    {
        m_space_rocks[i].Reset();//generate new random information
    }
}

SolarSystem::~SolarSystem()
{
    for(sdl_gui::Label* label : m_labels)
        delete(label);
    m_labels.clear();
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

    m_sun.Move(delta_time);
    m_sun_twin.Move(delta_time);
    m_mercury.Move(delta_time);
    m_venus.Move(delta_time);
    m_terra.Move(delta_time);
    m_luna.Move(delta_time);
    m_xeno.Move(delta_time);
}

void SolarSystem::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_SetRenderDrawColor(renderer, Colour::Black.r, Colour::Black.g, Colour::Black.b, Colour::Black.a);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, Colour::White.r, Colour::White.g, Colour::White.b, Colour::White.a);
    for(auto star : m_background_stars)
        SDL_RenderDrawPoint(renderer, star.X(), star.Y());

    if(m_show_orbit)
    {
        m_sun.RenderOrbit(renderer);
        m_sun_twin.RenderOrbit(renderer);
        m_mercury.RenderOrbit(renderer);
        m_venus.RenderOrbit(renderer);
        m_terra.RenderOrbit(renderer);
        m_luna.RenderOrbit(renderer);
        m_xeno.RenderOrbit(renderer);
    }

    m_sun.Render(renderer, delta_time);
    m_sun_twin.Render(renderer, delta_time);
    m_mercury.Render(renderer, delta_time);
    m_venus.Render(renderer, delta_time);
    m_terra.Render(renderer, delta_time);
    m_luna.Render(renderer, delta_time);
    m_xeno.Render(renderer, delta_time);

    for(sdl_gui::Label* label : m_labels)
        label->Render(delta_time);
}

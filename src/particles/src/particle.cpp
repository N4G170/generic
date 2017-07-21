#include "particle.hpp"
#include <utility>

//<f> Constructors & operator=
Particle::Particle(SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr)
{

}

Particle::~Particle() noexcept
{
    m_particle_texture = nullptr;
}

Particle::Particle(const Particle& other)
{

}

Particle::Particle(Particle&& other) noexcept
{

}

Particle& Particle::operator=(const Particle& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Particle& Particle::operator=(Particle&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f>

//<f> Methods
void Particle::Logic(float delta_time)
{

}

void Particle::FixedLogic(float fixed_delta_time)
{

}

void Particle::Render(float delta_time)
{
    if(m_particle_texture == nullptr)
        return;
}
//</f>

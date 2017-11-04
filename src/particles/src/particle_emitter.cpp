#include "particle_emitter.hpp"
#include <utility>
#include "image.hpp"
#include "particle.hpp"
#include "random.hpp"
#include "constants.hpp"
#include <cmath>
#include "utils.hpp"

//<f> Constructors & operator=
ParticleEmitter::ParticleEmitter(SystemManager* system_manager): BehaviourScript{}, m_system_manager{system_manager}
{

}

ParticleEmitter::~ParticleEmitter() noexcept
{

}

ParticleEmitter::ParticleEmitter(const ParticleEmitter& other)
{

}

ParticleEmitter::ParticleEmitter(ParticleEmitter&& other) noexcept
{

}

ParticleEmitter& ParticleEmitter::operator=(const ParticleEmitter& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ParticleEmitter& ParticleEmitter::operator=(ParticleEmitter&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* ParticleEmitter::Clone() { return new ParticleEmitter{*this}; }
//</f> /Virtual Methods

//<f> Particle Control
void ParticleEmitter::CreateParticle()
{
    for(auto i{0}; i<250; ++i)
    {
        auto particle_obj{m_system_manager->Objects()->CreateObject()};
        auto particle_img{new Image(m_system_manager)};
        particle_obj->AddScript(particle_img);

        // int img_index{Random(0,8)};
        // particle_img->SetImage("data/img/Explosion/explosion0"+std::to_string(img_index)+".png");
        particle_img->ColourModulation({128,0,0,255});

        particle_obj->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 0});
        particle_obj->TransformPtr()->LocalScale({5,5,0});

        auto particle_script{new Particle{}};

        particle_obj->AddScript(particle_script);

        float rotation{Random(1.f, 15.f)};
        auto angle{ DegreesToRadians(Random(90-25.f + 180, 90+25.f + 180)) };
        Vector3<float> direction{ std::cos(angle), std::sin(angle), 0};
        // Vector3<float> direction{ Random(-1.f, 1.f), Random(-1.f, 1.f), 0};
        float velocity{Random(1.f, 10.f) * 5};

        // particle_script->Config(1, {1,0,0}, 5, 0, false);
        particle_script->Config(1, direction, velocity, rotation, false);
        particle_script->Release();
    }
}
//</f> /Particle Control

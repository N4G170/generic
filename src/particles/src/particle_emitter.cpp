#include "particle_emitter.hpp"
#include <utility>
#include "image.hpp"
#include "particle.hpp"
#include "random.hpp"
#include "constants.hpp"
#include <cmath>
#include "utils.hpp"

//<f> Constructors & operator=
ParticleEmitter::ParticleEmitter(SystemManager* system_manager): BehaviourScript{}, m_system_manager{system_manager}, m_direction_angle{0}, m_number_of_particles{0}
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
    //to world
    auto world_mouse {m_system_manager->MainCamera()->ToWorldSpace({(float)m_input_event.motion.x, (float)m_input_event.motion.y, 0})};

    float spread{Random(20.f, 30.f)};
    m_number_of_particles = Random(250,500);
    for(auto i{0}; i<m_number_of_particles; ++i)
    {
        auto particle_obj{m_system_manager->Objects()->CreateObject()};
        auto particle_img{new Image(m_system_manager)};
        particle_obj->AddScript(particle_img);

        // int img_index{Random(0,8)};
        // particle_img->SetImage("data/img/Explosion/explosion0"+std::to_string(img_index)+".png");
        // particle_img->ColourModulation({128,0,0,255});
        particle_img->ColourModulation({(Uint8)Random(128,255),0,0,255});

        particle_obj->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 0});
        particle_obj->TransformPtr()->LocalScale({5,5,0});

        auto particle_script{new Particle{}};

        particle_obj->AddScript(particle_script);

        float rotation{Random(1.f, 15.f)};
        auto angle{ DegreesToRadians(Random(m_direction_angle-spread, m_direction_angle+spread)) };
        // auto angle{ DegreesToRadians(Random(90-25.f + 180, 90+25.f + 180)) };
        // auto angle{ DegreesToRadians(Random(0, 360)) };
        Vector3<float> direction{ std::cos(angle), std::sin(angle), 0};
        // Vector3<float> direction{ Random(-1.f, 1.f), Random(-1.f, 1.f), 0};
        float velocity{Random(1.f, 10.f) * 5};

        // particle_script->Config(1, {1,0,0}, 5, 0, false);
        particle_script->Config(1, direction, velocity, rotation, false);
        particle_script->Release();
    }
}
//</f> /Particle Control

#include "particle.hpp"
#include <utility>
#include "object.hpp"

//<f> Constructors & operator=
Particle::Particle()
{

}

Particle::~Particle() noexcept
{

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

//<f> Virtual Methods
Script* Particle::Clone() { return new Particle{*this}; }

void Particle::Update(float delta_time)
{
    if(m_released)
    {
        //get position
        auto position{m_owner->TransformPtr()->LocalPosition()};
        if(m_global_space)
            position = m_owner->TransformPtr()->GlobalPosition();

        position += m_direction * m_velocity;

        //set position
        if(m_global_space)
            m_owner->TransformPtr()->GlobalPosition(position);
        else
            m_owner->TransformPtr()->LocalPosition(position);


        auto rotation{m_owner->TransformPtr()->LocalRotation()};
        rotation.Z( rotation.Z() + m_rotation );
        m_owner->TransformPtr()->LocalRotation(rotation);

        //update ttl
        m_ttl -= delta_time;

        if(m_ttl <= 0)
            StopAndDestroy();
    }
}
//</f>

//<f> Methods
void Particle::Release() { m_released = true; }

void Particle::Stop() { m_released = false; }

void Particle::StopAndDestroy() { m_released = false; m_owner->Destroy(); }
//</f>

//<f> Getters/Setters
void Particle::Config(float ttl, const Vector3<float>& direction, float velocity, float z_rotation, bool in_global_space)
{
    TTL(ttl);
    Direction(direction);
    Velocity(velocity);
    Rotation(z_rotation);
    GlobalSpace(in_global_space);
}

float Particle::TTL() const { return m_ttl; }
void Particle::TTL(float ttl) { m_ttl = ttl; }

Vector3<float> Particle::Direction() const { return m_direction; }
void Particle::Direction(const Vector3<float>& direction) { m_direction = direction; m_direction.Normalize(); }

float Particle::Velocity() const { return m_velocity; }
void Particle::Velocity(float velocity) { m_velocity = velocity; }

float Particle::Rotation() const { return m_rotation; }
void Particle::Rotation(float rotation) { m_rotation = rotation; }

bool Particle::GlobalSpace() const { return m_global_space; }
void Particle::GlobalSpace(bool global_space) { m_global_space = global_space; }
//</f>

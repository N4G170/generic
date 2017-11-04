#include "planet.hpp"
#include "shapes.hpp"
#include <algorithm>
#include <iostream>
#include "object.hpp"
#include "random.hpp"
#include "utils.hpp"
#include "debug_render.hpp"

//<f> Constructor & operator=
Planet::Planet(): BehaviourScript(),  m_current_orbit_step{}, m_position_offset{}, m_current_angle{0}, m_angle_step{0.1f}, m_current_orbit_time{0}, m_orbit_update_interval{0.1f},
    m_rotation_angle{0}, m_rotation_step{0}, m_orbit{nullptr}
{
    //calculate initial position
    m_current_angle = Random(0.f, 360.f);
    m_current_orbit_step = GenerateRadianOrbitStep( m_perihelion, m_aphelion, DegreesToRadians(m_current_angle) );
}

Planet::~Planet() noexcept
{

}

Planet::Planet(const Planet& other)
{

}

Planet::Planet(Planet&& other) noexcept
{

}

Planet& Planet::operator=(const Planet& other)
{
    if(this != &other)
    {

    }
    return *this;
}

Planet& Planet::operator=(Planet&& other) noexcept
{
    if(this != &other)
    {

    }
    return *this;
}
//</f> /Constructor & operator=

//<f> Virtual Methods
Script* Planet::Clone() { return new Planet(*this); }

void Planet::Update(float delta_time)
{
    if(m_owner == nullptr)
        return;

    m_current_orbit_time += delta_time;

    if(m_current_orbit_time > m_orbit_update_interval)
    {
        //reset counter
        m_current_orbit_time = 0;

        auto position{m_owner->TransformPtr()->LocalPosition()};
        m_current_angle += m_angle_step;
        m_current_orbit_step = GenerateRadianOrbitStep( m_perihelion, m_aphelion, DegreesToRadians(m_current_angle) );

        auto position_offset{m_position_offset};
        if(m_rotation_step != 0)//applay rotation
        {
            m_rotation_angle += m_rotation_step;
            m_current_orbit_step = Rotate2D(m_current_orbit_step, {0,0,0}, DegreesToRadians(m_rotation_angle));
            position_offset = Rotate2D(position_offset, {0,0,0}, DegreesToRadians(m_rotation_angle));

            if(m_orbit != nullptr)
            {
                m_orbit->RotationAngle(m_rotation_angle);
                m_orbit->PositionOffset(position_offset);
            }
        }
        m_current_orbit_step += position_offset;

        position.X(m_current_orbit_step.X());
        position.Y(m_current_orbit_step.Y());

        m_owner->TransformPtr()->LocalPosition(position);
    }
}
//</f> /Virtual Methods

//<f> Get/Set
float Planet::AngleStep() const { return m_angle_step; }
void Planet::AngleStep(float angle_step) { m_angle_step = angle_step; }
float Planet::Perihelion() const { return m_perihelion; }
void Planet::Perihelion(float perihelion) { m_perihelion = perihelion; }
float Planet::Aphelion() const { return m_aphelion; }
void Planet::Aphelion(float aphelion) { m_aphelion = aphelion; }

/**
 * \brief Get the interval at which the orbit updates. The lower the faster it updates
 */
float  Planet::OrbitUpdateInterval() const { return m_orbit_update_interval; }
/**
 * \brief Set the interval at which the orbit updates. The lower the faster it updates
 */
void  Planet::OrbitUpdateInterval(float interval) { m_orbit_update_interval = interval; }

float Planet::Mass() const { return m_mass; }
void Planet::Mass(float mass) { m_mass = mass; }

void Planet::SetOrbitRender(OrbitRender* orbit_render) { m_orbit = orbit_render; }
OrbitRender* Planet::GetOrbitRender() const { return m_orbit; }

void Planet::RotationStep(float rotation_step) { m_rotation_step = rotation_step; }
float Planet::RotationStep() const { return m_rotation_step; }

void Planet::PositionOffset(const Vector3<float>& position_offset) { m_position_offset = position_offset; }
Vector3<float> Planet::PositionOffset() const { return m_position_offset; }
//</f> /Get/Set

//<f> Orbit
void Planet::RecalculateOrbit()
{
    if(m_orbit != nullptr)
    {
        auto orbit {GenerateFullOrbitRadianStep(m_perihelion, m_aphelion, DegreesToRadians(m_angle_step))};

        m_orbit->RebuildOrbit(m_perihelion, m_aphelion, orbit);
        m_orbit->PositionOffset(m_position_offset);
    }
}

Vector3<float> Planet::GenerateRadianOrbitStep(float perihelion, float aphelion, float radian_angle)
{
    return {aphelion * cos(radian_angle), perihelion * sin(radian_angle), 0};
}
Vector3<float> Planet::GenerateDegreeOrbitStep(float perihelion, float aphelion, float degree_angle)
{
    auto radian_angle{ DegreesToRadians(degree_angle)};
    return {aphelion * cos(radian_angle), perihelion * sin(radian_angle), 0};
}

std::vector<Vector3<float>> Planet::GenerateFullOrbitRadianStep(float perihelion, float aphelion, float radian_angle_step)
{
    //tmp
    if(radian_angle_step < 0)
        radian_angle_step *= -1;
    std::vector<Vector3<float>> orbit_storage{};
    float double_pi{(Math::PI * 2)};

    for(float angle{0}; angle <= double_pi; angle += radian_angle_step)//in rad (1º = 0.017rad)
    {
        //parametric form
        // x = a + radius * cos(t); with a being centre x and t the angle between 0 and 2PI
        // y = b + radius * sin(t); with a being centre y and t the angle between 0 and 2PI
        orbit_storage.push_back( {aphelion * cos(angle), perihelion * sin(angle), 0} );
    }

    return orbit_storage;
}
std::vector<Vector3<float>> Planet::GenerateFullOrbitDegreeStep(float perihelion, float aphelion, float degree_angle_step)
{
    return GenerateFullOrbitRadianStep(perihelion, aphelion, DegreesToRadians(degree_angle_step));
}
//</f> /Orbit

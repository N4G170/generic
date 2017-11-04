#include "drop.hpp"
#include "constants.hpp"
#include <iostream>
#include "random.hpp"
#include "object.hpp"
#include "utils.hpp"

//<f> Constructors & operator=
Drop::Drop(SystemManager* system_manager): BehaviourScript{}, m_velocity{}, m_wind{}
{
    m_splash_object = system_manager->Objects()->CreateObject();
    m_splash_animation = new BasicFrameAnimation();
    m_splash_object->AddScript(m_splash_animation);
    m_splash_object->TransformPtr()->LocalScale({9,6,1});
    m_splash_object->Disable();

    m_splash_animation->AddFrame("data/img/splash.png", true, {0,0,9,6});
    m_splash_animation->AddFrame("data/img/splash.png", true, {9,0,9,6});
    m_splash_animation->AddFrame("data/img/splash.png", true, {18,0,9,6});
    m_splash_animation->AddFrame("data/img/splash.png", true, {27,0,9,6});
    m_splash_animation->AddFrame("data/img/splash.png", true, {36,0,9,6});
    m_splash_animation->FPS(4);

    auto splash_img{ new Image{system_manager}};
    m_splash_animation->SetImage(splash_img);
    m_splash_object->AddScript(splash_img);
}

Drop::~Drop() noexcept {}

Drop::Drop(const Drop& other): BehaviourScript{other}, m_velocity{other.m_velocity}, m_wind{other.m_wind} {}

Drop::Drop(Drop&& other) noexcept: BehaviourScript{std::move(other)}, m_velocity{std::move(other.m_velocity)}, m_wind{std::move(other.m_wind)} {}

Drop& Drop::operator=(const Drop& other)
{
    if(this != &other)
    {
        auto tmp{other};
        *this = std::move(tmp);
    }
    return *this;
}
Drop& Drop::operator=(Drop&& other) noexcept
{
    if(this != &other)
    {
        BehaviourScript::operator=(std::move(other));
        m_velocity = std::move(other.m_velocity);
        m_wind = std::move(other.m_wind);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Drop* Drop::Clone() { return new Drop{*this}; }

void Drop::Update(float delta_time)
{
    if(m_owner == nullptr)
        return;

    //drop drop
    auto position{m_owner->TransformPtr()->LocalPosition()};
    auto size{m_owner->TransformPtr()->LocalScale()};

    position += (m_velocity + m_wind) * delta_time;

    if(position.Z() < c_min_drop_z || position.Z() > c_max_drop_z)
        ResetDrop();

    // size.Z(  );

    m_owner->TransformPtr()->LocalPosition(position);

    if(position.Y() > window_height - size.Y())//debug check
    {
        if(position.Z() < 6)
        {
            m_splash_object->TransformPtr()->LocalPositionX(position.X());
            m_splash_object->TransformPtr()->LocalPositionY(window_height - size.Y());
            m_splash_object->Enable();
            m_splash_animation->Play();
        }

        ResetDrop();
    }

    if(!m_splash_animation->IsPlaying())
    {
        m_splash_object->Disable();
        m_splash_animation->Stop();
    }
}
//</f> /Virtual Methods

//<f> Get/Set
Vector3<float> Drop::Velocity() const { return m_velocity; }
void Drop::Velocity(const Vector3<float>& velocity) { m_velocity = velocity; }

/**
 * \brief Apply a force to current velocity
 */
void Drop::ChangeVelocity(const Vector3<float>& force) { m_velocity += force; }

void Drop::ChangeWindForce(const Vector3<float>& wind) { m_wind = wind; }
//</f> /Get/Set

//<f> Methods
void Drop::DropHit(Collider* other)
{
    if(other->Owner()->HasTag("floor"))
    {
        ResetDrop();
    }
}

void Drop::ResetDrop()
{
    if(m_owner == nullptr)
        return;

    auto depth {Random( c_min_drop_z, c_max_drop_z )};
    auto size{m_owner->TransformPtr()->LocalScale()};

    auto drop_width{MapValueToRange(depth, c_min_drop_z, c_max_drop_z, c_min_drop_width, c_max_drop_width)};

    size.X( drop_width );//from 3 to 1
    size.Y( drop_width + 1 );//height = 2 * width
    m_owner->TransformPtr()->LocalScale(size);

    //position
    auto position{m_owner->TransformPtr()->LocalPosition()};
    position.X( Random( -c_max_wind_x_force, window_width + c_max_wind_x_force ) );
    position.Y( Random( -size.Y(), window_height * -1.f ) );
    position.Z( Random( c_min_drop_z, c_max_drop_z) );
    m_owner->TransformPtr()->LocalPosition(position);

    m_velocity = {0,1,0};//reset
    m_velocity *= (20 - depth) * 50;
}
//</f> /Methods

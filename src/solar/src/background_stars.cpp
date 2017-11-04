#include "background_stars.hpp"
#include <utility>
#include "constants.hpp"
#include "object.hpp"
#include "utils.hpp"

//<f> Constructors & operator=
BackgroundStars::BackgroundStars(): BehaviourScript{}, m_image{nullptr}, m_current_time{0}, m_update_interval{0.5f}
{

}

BackgroundStars::~BackgroundStars() noexcept
{

}

BackgroundStars::BackgroundStars(const BackgroundStars& other): BehaviourScript{other}, m_image{other.m_image}
{

}

BackgroundStars::BackgroundStars(BackgroundStars&& other) noexcept: BehaviourScript{std::move(other)}, m_image{std::move(other.m_image)}
{

}

BackgroundStars& BackgroundStars::operator=(const BackgroundStars& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

BackgroundStars& BackgroundStars::operator=(BackgroundStars&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
        BehaviourScript::operator=(std::move(other));
        m_image = std::move(other.m_image);
    }
    return *this;
}
//</f> /Constructors & operator=


//<f> Virtual Methods
Script* BackgroundStars::Clone() { return new BackgroundStars{*this}; }

void BackgroundStars::Update(float delta_time)
{
    if(m_owner == nullptr)
        return;

    m_current_time += delta_time;

    if(m_current_time > m_update_interval)
    {
        m_current_time = 0;

        auto position{m_owner->TransformPtr()->LocalPosition()};

        position = Rotate2D(position, {window_centre_x, window_centre_y, 0.f}, DegreesToRadians(m_angle));

        m_owner->TransformPtr()->LocalPosition(position);
    }
}

//</f> /Virtual Methods

//<f> Getters/Setters
float BackgroundStars::UpdateInterval() const { return m_update_interval; }
void BackgroundStars::UpdateInterval(float interval) { m_update_interval = interval; }

float BackgroundStars::RotationAngle() const { return m_angle; }
void BackgroundStars::RotationAngle(float angle) { m_angle = angle; }
//</f> /Getters/Setters

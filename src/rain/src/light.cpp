#include "light.hpp"
#include <utility>
#include "object.hpp"
#include <iostream>

//<f> Constructors & operator=
Light::Light()
{

}

Light::~Light() noexcept
{

}

Light::Light(const Light& other)
{

}

Light::Light(Light&& other) noexcept
{

}

Light& Light::operator=(const Light& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Light& Light::operator=(Light&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Light::Clone() { return new Light{*this}; }

void Light::Update(float delta_time)
{
    auto position{m_owner->TransformPtr()->LocalPosition()};
    position.X( m_input_event.motion.x );
    position.Y( m_input_event.motion.y );
    m_owner->TransformPtr()->LocalPosition(position);
}
//</f> /Virtual Methods

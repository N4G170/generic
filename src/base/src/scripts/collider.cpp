#include "collider.hpp"
#include <utility>
#include "utils.hpp"
#include <iostream>
#include "object.hpp"

//<f> Constructors & operator=
Collider::Collider() : Script{}, OnCollision{}, m_local_position{0,0,0}, m_scale{1,1,1} {}

Collider::~Collider() noexcept {}

Collider::Collider(const Collider& other): Script{other}, OnCollision{other.OnCollision}, m_local_position{other.m_local_position}, m_scale{other.m_scale} {}

Collider::Collider(Collider&& other) noexcept: Script{std::move(other)}, OnCollision{std::move(other.OnCollision)},
    m_local_position{std::move(other.m_local_position)}, m_scale{std::move(other.m_scale)}
{

}

Collider& Collider::operator=(const Collider& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Collider& Collider::operator=(Collider&& other) noexcept
{
    if(this != &other)//not same ref
    {
        Script::operator=(std::move(other));
        OnCollision = std::move(other.OnCollision);
        m_local_position = std::move(other.m_local_position);
        m_scale = std::move(other.m_scale);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Collider::Clone() { return new Collider{*this}; }
//</f> /Virtual Methods

//<f> Getters/Setters
Vector3<float> Collider::ColliderLocalPosition() const { return m_local_position; }
void Collider::ColliderLocalPosition(const Vector3<float>& position) { m_local_position = position; }

Vector3<float> Collider::ColliderScale() const {return m_scale; }
void Collider::ColliderScale(const Vector3<float>& scale) { m_scale = scale; }


Bounds<float> Collider::GlobalBounds() const
{
    if(m_owner != nullptr)
    {
        auto anchor{m_owner->TransformPtr()->Anchor()};
        auto final_collider_position{ m_owner->TransformPtr()->GlobalPosition() + m_local_position };
        auto size{ m_owner->TransformPtr()->GlobalScale() * m_scale };

        final_collider_position = AjustPositionToAnchor(final_collider_position, size, anchor);

        return {final_collider_position, size};
    }

    return {m_local_position, m_scale};
}

Vector3<float> Collider::BoundRadiusVector() const
{
    auto radius = Vector3<float>{0,0,0};

    auto bounds{GlobalBounds()};

    radius.X( (bounds.max_x - bounds.min_x) / 2 );
    radius.Y( (bounds.max_y - bounds.min_y) / 2 );
    radius.Z( (bounds.max_z - bounds.min_z) / 2 );

    return radius;
}
//</f> /Getters/Setters

//<f> Collision
void Collider::CheckCollision(Collider* other)
{
    if(BoundsCollision(GlobalBounds(), other->GlobalBounds()))
    {
        if(OnCollision)
            OnCollision(other);
    }
}
//</f> /Collision

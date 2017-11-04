#include "comet.hpp"
#include <algorithm>
#include "random.hpp"
#include "constants.hpp"
#include "object.hpp"
#include "utils.hpp"

//<f> Constructors & operator=
/** Default constructor */
Comet::Comet(): BehaviourScript{}, m_velocity{Random(100.f,250.f)}, m_direction{0,0,0}, m_can_reset{false}
{

}

/** Destructor */
Comet::~Comet() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
{

}

/** Copy constructor */
Comet::Comet (const Comet& other): BehaviourScript{other}, m_velocity{other.m_velocity}, m_direction{other.m_direction}, m_can_reset{other.m_can_reset}
{

}

/** Move constructor */
Comet::Comet (Comet&& other) noexcept: BehaviourScript{std::move(other)}, m_velocity{std::move(other.m_velocity)}, m_direction{std::move(other.m_direction)},
    m_can_reset{std::move(other.m_can_reset)}
{

}

/** Copy assignment operator */
Comet& Comet::operator= (const Comet& other)
{
    if(this != &other)
    {
        auto tmp(other);         // re-use copy-constructor
        *this = std::move(tmp); // re-use move-assignment
    }
    return *this;
}

/** Move assignment operator */
Comet& Comet::operator= (Comet&& other) noexcept
{
    if(this != &other)
    {
        BehaviourScript::operator=(std::move(other));
        m_velocity = std::move(other.m_velocity);
        m_direction = std::move(other.m_direction);
        m_can_reset = std::move(other.m_can_reset);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Comet::Clone(){ return new Comet(*this); }

void Comet::Update(float delta_time)
{
    auto position{ m_owner->TransformPtr()->LocalPosition() };
    position = position + m_direction * m_velocity * delta_time;
    m_owner->TransformPtr()->LocalPosition(position);

    //check if inside window
    if(RectCollision(position, m_owner->TransformPtr()->LocalScale(), {0,0,0}, {window_width, window_height, 0}))
    {
        m_can_reset = true;
    }
    else if(m_can_reset)
    {
        m_can_reset = false;
        Reset();//prepare for new run
    }
}
//</f> /Virtual Methods

//<f> Methods
void Comet::Accelerate(float acceleration)
{
    m_velocity += acceleration;
}

void Comet::Reset()
{
    //calculate entry point
    auto source{Random(0,3)};//wasd -> 0123
    if(source == 0)//top
    {
        auto position{ m_owner->TransformPtr()->LocalPosition() };
        position.X(Random( 0, window_width ));
        position.Y(Random( -5, 0 ));
        m_owner->TransformPtr()->LocalPosition(position);
    }
    else if(source == 1)//left
    {
        auto position{ m_owner->TransformPtr()->LocalPosition() };
        position.X(Random( -5, 0 ));
        position.Y(Random( 0, window_height ));
        m_owner->TransformPtr()->LocalPosition(position);
    }
    else if(source == 2)//bottom
    {
        auto position{ m_owner->TransformPtr()->LocalPosition() };
        position.X(Random( 0, window_width ));
        position.Y(Random( window_height, window_height + 5 ));
        m_owner->TransformPtr()->LocalPosition(position);
    }
    else if(source == 3)//right
    {
        auto position{ m_owner->TransformPtr()->LocalPosition() };
        position.X(Random( window_width, window_width + 5 ));
        position.Y(Random( 0, window_height ));
        m_owner->TransformPtr()->LocalPosition(position);
    }

    //calculate destination
    auto destination{source};
    while( destination == source)
    {
        destination = Random(0,3);//wasd -> 0123
    }
    auto target_position{ m_owner->TransformPtr()->LocalPosition() };

    if(destination == 0)//top
    {
        target_position.X(Random( 0, window_width ));
        target_position.Y(Random( -5, 0 ));
    }
    else if(destination == 1)//left
    {
        target_position.X(Random( -5, 0 ));
        target_position.Y(Random( 0, window_height ));
    }
    else if(destination == 2)//bottom
    {
        target_position.X(Random( 0, window_width ));
        target_position.Y(Random( window_height, window_height + 5 ));
    }
    else if(destination == 3)//right
    {
        target_position.X(Random( window_width, window_width + 5 ));
        target_position.Y(Random( 0, window_height ));
    }

    //calculate initial direction vector
    m_direction = target_position - m_owner->TransformPtr()->LocalPosition();
    m_direction.Normalize();
}

void Comet::InfluenceDirection(const Vector3<float>& force)
{
    m_direction += force;
    m_direction.Normalize();
}
Vector3<float> Comet::Direction() const { return m_direction; }

void Comet::OnCollision(Collider* other)
{
    Reset();
}
//</f> /Methods

#include "sdl_gui_collider.hpp"
#include <utility>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

// <f> < GUI_COLLIDER_SHAPE >

ColliderShape::ColliderShape(const Position& position, const Dimensions& dimensions, GuiTransform* owner_transform): m_type{ColliderShapeType::BOX},
    m_local_position{position}, m_dimensions{dimensions}, m_owner_transform{owner_transform}
{
    IsPointColliding = std::bind(&ColliderShape::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

ColliderShape::ColliderShape(const Position& position, int circle_radius, GuiTransform* owner_transform): m_type{ColliderShapeType::CIRCLE}, m_local_position{position},
    m_circle_collider_radius{circle_radius}, m_squared_radius{circle_radius*circle_radius}, m_owner_transform{owner_transform}
{
    IsPointColliding = std::bind(&ColliderShape::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

ColliderShape::~ColliderShape()
{

}

ColliderShape::ColliderShape(const ColliderShape& other): m_type{other.m_type}, m_local_position{other.m_local_position}, m_dimensions{other.m_dimensions},
    m_circle_collider_radius{other.m_circle_collider_radius}, m_squared_radius{other.m_squared_radius}, m_owner_transform{other.m_owner_transform}
{
    SetCollisionDetectionFunction();
}

ColliderShape::ColliderShape(ColliderShape&& other)
{
    m_type = std::move(other.m_type);
    m_dimensions = std::move(other.m_dimensions);
    m_circle_collider_radius = std::move(other.m_circle_collider_radius);
    m_squared_radius = std::move(other.m_squared_radius);
    m_owner_transform = std::move(other.m_owner_transform);
}

ColliderShape& ColliderShape::operator= (const ColliderShape& other)
{
    if(&other != this)//different instance
    {
        SetCollisionDetectionFunction();

        m_type = other.m_type;
        m_dimensions = other.m_dimensions;
        m_circle_collider_radius = other.m_circle_collider_radius;
        m_squared_radius = other.m_squared_radius;
        m_owner_transform = other.m_owner_transform;
    }
    return *this;
}

ColliderShape& ColliderShape::operator= (ColliderShape&& other)
{
    if(&other != this)//different instance
    {
        SetCollisionDetectionFunction();

        m_type = std::move(other.m_type);
        m_dimensions = std::move(other.m_dimensions);
        m_circle_collider_radius = std::move(other.m_circle_collider_radius);
        m_squared_radius = std::move(other.m_squared_radius);
        m_owner_transform = std::move(other.m_owner_transform);
    }
    return *this;
}

/* PRIVATE FUNCTIONS */
void ColliderShape::SetCollisionDetectionFunction()
{
    if(m_type == ColliderShapeType::BOX)
        IsPointColliding = std::bind(&ColliderShape::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
    else if(m_type == ColliderShapeType::CIRCLE)
        IsPointColliding = std::bind(&ColliderShape::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

bool ColliderShape::BoxPointCollision(int mouse_x, int mouse_y)
{
    Position final_position = m_owner_transform->GlobalPosition();

    final_position.x += m_local_position.x;
    final_position.y += m_local_position.y;

    return (mouse_x >= final_position.x && mouse_x < (m_dimensions.w + final_position.x)) && (mouse_y >= final_position.y && mouse_y < (m_dimensions.h + final_position.y));
}

bool ColliderShape::CirclePointCollision(int mouse_x, int mouse_y)
{
    // int x = (mouse_x - m_circle_centre.x);
    // int y = (mouse_y - m_circle_centre.y);
    // return (x * x + y * y) <= m_squared_radius;
    int x = (mouse_x - m_local_position.x - m_owner_transform->GlobalPosition().x);
    int y = (mouse_y - m_local_position.y - m_owner_transform->GlobalPosition().y);
    return (x * x + y * y) <= m_squared_radius;
}

// </f> < GUI_COLLIDER_SHAPE >


// <f> < GUI_COLLIDER >
/* Box constructor */
Collider::Collider(const Position& position, const Dimensions& rect_collider, GuiTransform* owner_transform): m_shapes{ColliderShape{position, rect_collider, owner_transform}},
    m_previous_mouse_in{false}, m_mouse_in{false}, m_owner_transform{owner_transform}
{

}
/* Circle constructor */
Collider::Collider(const Position& position, int circle_radius, GuiTransform* owner_transform): m_shapes{ColliderShape{position, circle_radius, owner_transform}},
    m_previous_mouse_in{false}, m_mouse_in{false}, m_owner_transform{owner_transform}
{

}

Collider::~Collider() noexcept
{

}

Collider::Collider(const Collider& other): m_shapes{other.m_shapes}, m_owner_transform{other.m_owner_transform}
{

}

Collider::Collider(Collider&& other) noexcept
{
    m_shapes = std::move(other.m_shapes);
    m_owner_transform = std::move(other.m_owner_transform);
}

Collider& Collider::operator=(const Collider& other)
{
    if(this != &other)//not same ref
    {
        Collider tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Collider& Collider::operator=(Collider&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_shapes = std::move(other.m_shapes);
        m_owner_transform = std::move(other.m_owner_transform);
    }

    return *this;
}

void Collider::SetColliderShape(const Position& position, const Dimensions& dimensions)
{
    m_shapes.push_back(ColliderShape{position, dimensions, m_owner_transform});
}

void Collider::SetColliderShape(const Position& centre_position, int circle_radius)
{
    m_shapes.push_back(ColliderShape{centre_position, circle_radius, m_owner_transform});
}

void Collider::ProcessFlags()
{
    if(MouseEnterCallBack && !m_previous_mouse_in && m_previous_mouse_in != m_mouse_in)//enter
    {
        MouseEnterCallBack();
    }
    else if(MouseInCallBack && m_mouse_in)//in
    {
        MouseInCallBack();
    }
    else if(MouseExitCallBack && m_previous_mouse_in && m_previous_mouse_in != m_mouse_in)//exit
    {
        MouseExitCallBack();
    }

    m_previous_mouse_in = m_mouse_in;
}

/* colliders */
bool Collider::IsPointColliding(int mouse_x, int mouse_y)
{
    for(const ColliderShape& shape : m_shapes)
    {
        if(shape.IsPointColliding(mouse_x, mouse_y))
            return true;
    }
    return false;
}

// </f> < GUI_COLLIDER >
}//namespace
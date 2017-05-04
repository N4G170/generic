#include "gui_collider.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

/* Box constructor */
GuiCollider::GuiCollider(const SDL_Rect& collider_dimensions): m_type{GuiColliderType::BOX}, m_rect_collider{collider_dimensions},
    m_circle_collider_radius{0}, m_squared_radius{0}
{
    IsPointColliding = std::bind(&GuiCollider::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
}
/* Circle constructor */
GuiCollider::GuiCollider(int centre_x, int centre_y, int circle_radius): m_type{GuiColliderType::CIRCLE}, m_circle_collider_radius{circle_radius}, m_squared_radius{circle_radius*circle_radius},
    m_centre_x{centre_x}, m_centre_y{centre_y}
{
    // IsPointColliding = std::bind(&GuiCollider::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

GuiCollider::~GuiCollider() noexcept
{

}

GuiCollider::GuiCollider(const GuiCollider& other): IsPointColliding{other.IsPointColliding}, m_type{other.m_type}, m_rect_collider{other.m_rect_collider},
    m_circle_collider_radius{other.m_circle_collider_radius}, m_squared_radius{other.m_squared_radius}
{

}

GuiCollider::GuiCollider(GuiCollider&& other) noexcept
{
    m_type = std::move(other.m_type);
    m_rect_collider = std::move(other.m_rect_collider);
    m_circle_collider_radius = std::move(other.m_circle_collider_radius);
    m_squared_radius = std::move(other.m_squared_radius);

    //callbacks using this pointer cannot be moved and must be reassigned
    if(m_type == GuiColliderType::BOX)
        IsPointColliding = std::bind(&GuiCollider::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

GuiCollider& GuiCollider::operator=(const GuiCollider& other)
{
    if(this != &other)//not same ref
    {
        GuiCollider tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiCollider& GuiCollider::operator=(GuiCollider&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_type = std::move(other.m_type);
        m_rect_collider = std::move(other.m_rect_collider);
        m_circle_collider_radius = std::move(other.m_circle_collider_radius);
        m_squared_radius = std::move(other.m_squared_radius);

        //callbacks using this pointer cannot be moved and must be reassigned
        if(m_type == GuiColliderType::BOX)
            IsPointColliding = std::bind(&GuiCollider::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
    }

    return *this;
}

void GuiCollider::SetCollider(const SDL_Rect& collider_dimensions)
{
    m_rect_collider = collider_dimensions;

    if(m_type != GuiColliderType::BOX)//we change collision detection
    {
        IsPointColliding = std::bind(&GuiCollider::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
        m_type = GuiColliderType::BOX;
    }
}

void GuiCollider::SetCollider(int centre_x, int centre_y, int circle_radius)
{
    m_centre_x = centre_x;
    m_centre_y = centre_y;
    m_circle_collider_radius = circle_radius;
    m_squared_radius = circle_radius * circle_radius;

    if(m_type != GuiColliderType::CIRCLE)//we change collision detection
    {
        IsPointColliding = std::bind(&GuiCollider::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
        m_type = GuiColliderType::CIRCLE;
    }
}

/* colliders */
bool GuiCollider::BoxPointCollision(int mouse_x, int mouse_y)
{
    return (mouse_x >= m_rect_collider.x && mouse_x <= (m_rect_collider.w + m_rect_collider.x)) && (mouse_y >= m_rect_collider.y && mouse_y <= (m_rect_collider.h + m_rect_collider.y));
}

bool GuiCollider::CirclePointCollision(int mouse_x, int mouse_y)
{
    int x = (mouse_x - m_centre_x);
    int y = (mouse_y - m_centre_y);
    return (x * x + y * y) <= m_squared_radius;
}

}//namespace

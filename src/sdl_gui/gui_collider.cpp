#include "gui_collider.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{

// <f> < GUI_COLLIDER_SHAPE >

GuiColliderShape::GuiColliderShape(const SDL_Rect& collider_dimensions): m_type{GuiColliderShapeType::BOX}, m_rect_collider{collider_dimensions}
{
    IsPointColliding = std::bind(&GuiColliderShape::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

GuiColliderShape::GuiColliderShape(int centre_x, int centre_y, int circle_radius): m_type{GuiColliderShapeType::CIRCLE}, m_circle_centre{centre_x, centre_y},
    m_circle_collider_radius{circle_radius}, m_squared_radius{circle_radius*circle_radius}
{
    IsPointColliding = std::bind(&GuiColliderShape::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

GuiColliderShape::~GuiColliderShape()
{

}

GuiColliderShape::GuiColliderShape(const GuiColliderShape& other): m_type{other.m_type}, m_rect_collider{other.m_rect_collider},
    m_circle_collider_radius{other.m_circle_collider_radius}, m_squared_radius{other.m_squared_radius}
{
    SetCollisionDetectionFunction();
}

GuiColliderShape::GuiColliderShape(GuiColliderShape&& other)
{
    m_type = std::move(other.m_type);
    m_rect_collider = std::move(other.m_rect_collider);
    m_circle_collider_radius = std::move(other.m_circle_collider_radius);
    m_squared_radius = std::move(other.m_squared_radius);
}

GuiColliderShape& GuiColliderShape::operator= (const GuiColliderShape& other)
{
    if(&other != this)//different instance
    {
        SetCollisionDetectionFunction();
    }
    return *this;
}

GuiColliderShape& GuiColliderShape::operator= (GuiColliderShape&& other)
{
    if(&other != this)//different instance
    {
        SetCollisionDetectionFunction();
    }
    return *this;
}

/* PRIVATE FUNCTIONS */
void GuiColliderShape::SetCollisionDetectionFunction()
{
    if(m_type == GuiColliderShapeType::BOX)
        IsPointColliding = std::bind(&GuiColliderShape::BoxPointCollision, this, std::placeholders::_1, std::placeholders::_2);
    else if(m_type == GuiColliderShapeType::CIRCLE)
        IsPointColliding = std::bind(&GuiColliderShape::CirclePointCollision, this, std::placeholders::_1, std::placeholders::_2);
}

bool GuiColliderShape::BoxPointCollision(int mouse_x, int mouse_y)
{
    return (mouse_x >= m_rect_collider.x && mouse_x <= (m_rect_collider.w + m_rect_collider.x)) && (mouse_y >= m_rect_collider.y && mouse_y <= (m_rect_collider.h + m_rect_collider.y));
}

bool GuiColliderShape::CirclePointCollision(int mouse_x, int mouse_y)
{
    int x = (mouse_x - m_circle_centre.x);
    int y = (mouse_y - m_circle_centre.y);
    return (x * x + y * y) <= m_squared_radius;
}

// </f> < GUI_COLLIDER_SHAPE >


// <f> < GUI_COLLIDER >
/* Box constructor */
GuiCollider::GuiCollider(const SDL_Rect& collider_dimensions): m_shapes{GuiColliderShape{collider_dimensions}}
{

}
/* Circle constructor */
GuiCollider::GuiCollider(int centre_x, int centre_y, int circle_radius): m_shapes{GuiColliderShape{centre_x, centre_y, circle_radius}}
{

}

GuiCollider::~GuiCollider() noexcept
{

}

GuiCollider::GuiCollider(const GuiCollider& other): m_shapes{other.m_shapes}
{

}

GuiCollider::GuiCollider(GuiCollider&& other) noexcept
{
    m_shapes = std::move(other.m_shapes);
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
        m_shapes = std::move(other.m_shapes);
    }

    return *this;
}

void GuiCollider::SetColliderShape(const SDL_Rect& collider_dimensions)
{
    m_shapes.push_back(GuiColliderShape{collider_dimensions});
}

void GuiCollider::SetColliderShape(int centre_x, int centre_y, int circle_radius)
{
    m_shapes.push_back(GuiColliderShape{centre_x, centre_y, circle_radius});
}

void GuiCollider::ProcessFlags()
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
bool GuiCollider::IsPointColliding(int mouse_x, int mouse_y)
{
    for(const GuiColliderShape& shape : m_shapes)
    {
        if(shape.IsPointColliding(mouse_x, mouse_y))
            return true;
    }
    return false;
}

// </f> < GUI_COLLIDER >
}//namespace

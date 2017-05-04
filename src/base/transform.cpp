#include "transform.hpp"
#include <algorithm>

Transform::Transform(): m_width{0}, m_height{0}, m_scale{1}, m_parent{nullptr}
{

}

Transform::~Transform()
{
    if(m_parent != nullptr)
    {
        m_parent->RemoveChild(this);
        m_parent = nullptr;
    }

    m_children.clear();
}

void Transform::SetParent(Transform* parent)
{
    if(m_parent != nullptr)
        m_parent->RemoveChild(this);
    m_parent = parent;

    UpdateSDLRects();
}

void Transform::RemoveChild(Transform * child)
{
    auto result = std::find(m_children.begin(), m_children.end(), child);
    if(result != m_children.end())
        m_children.erase(result);
}

Vector2<float> Transform::GlobalPosition()
{
    if(m_parent == nullptr)
        return m_position;
    else
    {
        Vector2<float> global_position = m_position;
        Transform* parent = m_parent;
        while(parent != nullptr)
        {
            global_position += parent->Position();
            parent = parent->m_parent;
        }
        return global_position;
    }
}

void Transform::UpdateSDLRects()
{
    m_sdl_rect.x = m_position.X();
    m_sdl_rect.y = m_position.Y();
    m_sdl_rect.w = m_width;
    m_sdl_rect.h = m_height;

    m_global_sdl_rect.x = GlobalPosition().X();
    m_global_sdl_rect.y = GlobalPosition().Y();
    m_global_sdl_rect.w = m_width;
    m_global_sdl_rect.h = m_height;
}

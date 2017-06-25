#include "sdl_gui_transform.hpp"
#include <utility>
#include <algorithm>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

GuiTransform::GuiTransform(UID owner_uid): m_uid{owner_uid}, m_global_position{0,0}, m_local_position{0,0}, m_size{0,0},
    m_parent{nullptr}, m_children{}
{
    m_parent_viewport = nullptr;

}

GuiTransform::~GuiTransform() noexcept
{

}

GuiTransform::GuiTransform(const GuiTransform& other): m_uid{other.m_uid}, m_global_position{other.m_global_position}, m_local_position{other.m_local_position}, m_size{other.m_size},
    m_parent_viewport{other.m_parent_viewport}, m_parent{other.m_parent}, m_children{other.m_children}
{
    if(m_parent != nullptr)
        m_parent->AddChild(this);
}

GuiTransform::GuiTransform(const GuiTransform& other, UID owner_uid): m_uid{owner_uid}, m_global_position{other.m_global_position}, m_local_position{other.m_local_position}, m_size{other.m_size},
    m_parent_viewport{other.m_parent_viewport}, m_parent{other.m_parent}, m_children{other.m_children}
{
    if(m_parent != nullptr)
        m_parent->AddChild(this);
}

GuiTransform::GuiTransform(GuiTransform&& other) noexcept
{
    m_uid = std::move(other.m_uid);
    m_global_position = std::move(other.m_global_position);
    m_local_position = std::move(other.m_local_position);
    m_size = std::move(other.m_size);
    m_parent_viewport = std::move(other.m_parent_viewport);
    m_parent = std::move(other.m_parent);
    m_children = std::move(other.m_children);
}

GuiTransform& GuiTransform::operator=(const GuiTransform& other)
{
    if(this != &other)//not same ref
    {
        GuiTransform tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiTransform& GuiTransform::operator=(GuiTransform&& other) noexcept
{
    m_uid = std::move(other.m_uid);
    m_global_position = std::move(other.m_global_position);
    m_local_position = std::move(other.m_local_position);
    m_size = std::move(other.m_size);
    m_parent_viewport = std::move(other.m_parent_viewport);
    m_parent = std::move(other.m_parent);
    m_children = std::move(other.m_children);

    return *this;
}

/* < Getters / Setters > */
Position GuiTransform::GlobalPosition() const
{
    if(m_parent == nullptr)
        return m_global_position;
    else
        return m_parent->GlobalPosition() + m_local_position;
}

void GuiTransform::GlobalPosition(const Position& new_global_position)
{
    if(m_global_position != new_global_position)
    {
        m_global_position = new_global_position;

        if(m_parent != nullptr)//update local position
            m_local_position = m_parent->GlobalPosition() - m_global_position;
    }
}

void GuiTransform::LocalPosition(const Position& new_local_position)
{
    if(m_local_position != new_local_position)
    {
        m_local_position = new_local_position;
        if(m_parent == nullptr)//local is also global position
            GlobalPosition(m_local_position);
    }
}

void GuiTransform::Size(const Dimensions& new_size)
{
    m_size = new_size;
}

void GuiTransform::ParentViewport(sdl_gui::GuiTransform *parent_viewport)
{
    // if(*m_inside_viewport != *inside_viewport)
    {
        m_parent_viewport = parent_viewport;

        for(GuiTransform*& child : m_children)
            child->ParentViewport(parent_viewport);
    }
}

SDL_Rect GuiTransform::RenderRect()
{
    if(m_parent != nullptr)
    {
        // if(m_inside_viewport)
        // {
        //     if(m_parent->IsViewport())
        //     {
        //         return {m_local_position.x, m_local_position.y, m_dimensions.w, m_dimensions.h };
        //     }
        //     else//child of a viewport child
        //     {
        //         int x{0}, y{0};
        //         GuiTransform* parent = m_parent;
        //         while(!parent->IsViewport())//we need to get the local position of all elements above, up to the viewport
        //         {
        //             x += parent->LocalPosition().x;
        //             y += parent->LocalPosition().y;
        //             parent = parent->m_parent;
        //         }
        //
        //         return {x + m_local_position.x, y + m_local_position.y, m_dimensions.w, m_dimensions.h };
        //     }
        // }
        if(m_parent_viewport)
        {
            //We need to remove the position of the viewport because the viewport "sets" a new origin
            return {m_parent->GlobalPosition().x + m_local_position.x - m_parent_viewport->GlobalPosition().x,
                    m_parent->GlobalPosition().y + m_local_position.y - m_parent_viewport->GlobalPosition().y, m_size.w, m_size.h };
        }
        else
            return {m_parent->GlobalPosition().x + m_local_position.x, m_parent->GlobalPosition().y + m_local_position.y, m_size.w, m_size.h };
    }
    else
        return {m_global_position.x, m_global_position.y, m_size.w, m_size.h };
}

void GuiTransform::Parent(GuiTransform* parent)
{
    if(parent != nullptr)//new parent
    {
        if(m_parent != nullptr)//we swap parents
        {
            //remove previous child link
            m_parent->RemoveChild(m_uid);
            //set new parent
            m_parent = parent;
            //set new child link
            m_parent->AddChild(this);
            //Recalculate positions
            RecalculateLocalPosition();
        }
        else//we add new parent
        {
            m_parent = parent;//set new parent
            //set new child link
            m_parent->AddChild(this);
            //Recalculate positions
            RecalculateLocalPosition();
        }
    }
    else if(m_parent != nullptr)//we remove current parent
    {
        //remove previous child link
        m_parent->RemoveChild(m_uid);
        //set new parent
        m_parent = parent;
    }
    //else we do nothing (means that m_parent == parent == nullptr)
}

GuiTransform* GuiTransform::Parent() const { return m_parent; }

void GuiTransform::AddChild(GuiTransform* child)
{
    m_children.push_back(child);
}

void GuiTransform::RemoveChild(UID child_uid)
{
    //remove child with same id
    m_children.erase( std::find_if(begin(m_children), end(m_children), [child_uid](GuiTransform* child)->bool {return child->m_uid == child_uid; } ) );
}

/* </ Getters / Setters > */

/* < Private Methods > */
void GuiTransform::RecalculateLocalPosition()
{
    if(m_parent)
        m_local_position = m_global_position - m_parent->GlobalPosition();
    else
        m_local_position = {0,0};
}
/* </ Private Methods > */
}//namespace

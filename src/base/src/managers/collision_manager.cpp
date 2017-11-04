#include "collision_manager.hpp"
#include <utility>
#include <algorithm>
#include <iostream>

//<f> Constructors & operator=
CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager() noexcept
{

}

CollisionManager::CollisionManager(const CollisionManager& other)
{

}

CollisionManager::CollisionManager(CollisionManager&& other) noexcept
{

}

CollisionManager& CollisionManager::operator=(const CollisionManager& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

CollisionManager& CollisionManager::operator=(CollisionManager&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Methods
void CollisionManager::AddCollider(Collider* collider)
{
    auto result{ std::find_if(std::begin(m_colliders), std::end(m_colliders), [collider](auto stored_collider)->bool { return collider->InstanceID() == stored_collider->InstanceID();}) };

    if(result == std::end(m_colliders))//not found
    {
        m_colliders.push_back(collider);
    }
}
void CollisionManager::RemoveCollider(UID instance_id)
{
    auto result{ std::find_if(std::begin(m_colliders), std::end(m_colliders), [instance_id](auto stored_collider)->bool { return instance_id == stored_collider->InstanceID();}) };

    if(result != std::end(m_colliders))//found
    {
        m_colliders.erase(result);
    }
}

void CollisionManager::FixedLogic(float fixed_delta_time)
{
    for(auto i{0}; i<m_colliders.size(); ++i)
    {
        if(m_colliders[i]->Enabled())
        {
            for(auto j{i + 1}; j<m_colliders.size(); ++j)
            {
                if(m_colliders[j]->Enabled())
                {
                    m_colliders[i]->CheckCollision(m_colliders[j]);
                    m_colliders[j]->CheckCollision(m_colliders[i]);
                }
            }
        }
    }
}

void CollisionManager::Clear()
{
    m_colliders.clear();
}
//</f> /Methods

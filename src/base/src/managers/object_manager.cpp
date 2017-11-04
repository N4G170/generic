#include "object_manager.hpp"
#include <utility>
#include <algorithm>
#include <iostream>

//<f> Constructors & operator=
ObjectManager::ObjectManager(): m_objects{}
{

}

ObjectManager::~ObjectManager() noexcept
{

}

ObjectManager::ObjectManager(const ObjectManager& other)
{

}

ObjectManager::ObjectManager(ObjectManager&& other) noexcept
{

}

ObjectManager& ObjectManager::operator=(const ObjectManager& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ObjectManager& ObjectManager::operator=(ObjectManager&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Object Methods
void ObjectManager::Input(const SDL_Event& event)
{
    for(auto& object : m_objects)
        if(object->Enabled())
            object->Input(event);
}
void ObjectManager::Logic(float delta_time)
{
    for(auto& object : m_objects)
        if(object->Enabled())
            object->Update(delta_time);
}
void ObjectManager::FixedLogic(float fixed_delta_time)
{
    for(auto& object : m_objects)
        if(object->Enabled())
            object->FixedUpdate(fixed_delta_time);
}
void ObjectManager::Render(float delta_time)
{
    //order by z position; the greater the value the further back (drawn first)
    if(!std::is_sorted(std::begin(m_objects), std::end(m_objects), [](auto& lhs, auto& rhs){ return lhs->TransformPtr()->GlobalPosition().Z() > rhs->TransformPtr()->GlobalPosition().Z(); }))
        std::sort( std::begin(m_objects), std::end(m_objects), [](auto& lhs, auto& rhs){ return lhs->TransformPtr()->GlobalPosition().Z() > rhs->TransformPtr()->GlobalPosition().Z(); } );

    for(auto& object : m_objects)
        if(object->Enabled())
            object->Render(delta_time);
}

void ObjectManager::Clear()
{
    m_objects.clear();
}
//</f> /Object Methods

//<f> Object Management
/**
 * \brief Creates a new empty object and returns a pointer to it
 */
Object* ObjectManager::CreateObject()
{
    Object* obj = new Object(this);
    m_objects.emplace_back(std::unique_ptr<Object>(obj));

    return m_objects.back().get();
}
/**
 * \brief Checks if the object with the given UID exists and returns a pointer to it, nullptr otherwise
 */
Object* ObjectManager::FindObject(UID instance_id)
{
    auto result = std::find_if( std::begin(m_objects), std::end(m_objects), [instance_id](auto& object)->bool { return object->InstanceID() ==instance_id; } );

    if(result != std::end(m_objects))//found
        return result->get();

    return nullptr;
}
/**
 * \brief Checks if the object with the given UID exists and returns a pointer to it, while releasing it from this class
 * \n meaning that it will no longer be managed by this manager. nullptr otherwise
 */
Object* ObjectManager::ReleaseObject(UID instance_id)
{
    auto result = std::find_if( std::begin(m_objects), std::end(m_objects), [instance_id](auto& object)->bool { return object->InstanceID() ==instance_id; } );

    if(result != std::end(m_objects))
    {
        //release pointer
        auto pointer{result->release()};
        //delete entry
        m_objects.erase(result);

        return pointer;
    }

    return nullptr;
}
/**
 * \brief Deletes the object whith the given UID (if it exists). Return true on success, false otherwise
 */
bool ObjectManager::DeleteObject(UID instance_id)
{
    auto result = std::find_if( std::begin(m_objects), std::end(m_objects), [instance_id](auto& object)->bool { return object->InstanceID() ==instance_id; } );

    if(result != std::end(m_objects))
    {
        //delete entry
        m_objects.erase(result);

        return true;
    }

    return false;
}
//</f> /Object Management

//<f> Getters/Setters
bool ObjectManager::HasObjectsToDestroy() const { return m_has_objects_to_destroy; }
void ObjectManager::HasObjectsToDestroy(bool has_objects_to_destroy) { m_has_objects_to_destroy = has_objects_to_destroy; }

void ObjectManager::DestroyMarked()
{
    auto begin_it{std::begin(m_objects)};
    for(int i{(int)m_objects.size() - 1}; i >= 0; --i)
    {
        if(m_objects[i]->MarkedForDestruction())
            m_objects.erase(begin_it + i);
    }

}
//</f> /Getters/Setters

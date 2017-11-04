#include "system_manager.hpp"
#include <utility>
#include <iostream>
#include "debug_render.hpp"

//<f> Constructors & operator=
SystemManager::SystemManager(SDL_Window* window, SDL_Renderer* renderer_ptr): m_resource_manager{renderer_ptr}, m_object_manager{}, m_collision_manager{},
    m_window{window}, m_renderer{renderer_ptr}, m_main_camera{renderer_ptr}
{
    DebugRender::Init(renderer_ptr);
}

SystemManager::~SystemManager() noexcept
{

}

SystemManager::SystemManager(const SystemManager& other): m_resource_manager{other.m_resource_manager}, m_object_manager{other.m_object_manager},
    m_collision_manager{other.m_collision_manager}, m_window{other.m_window}, m_renderer{other.m_renderer}, m_main_camera{other.m_main_camera}
{

}

SystemManager::SystemManager(SystemManager&& other) noexcept: m_resource_manager{std::move(other.m_resource_manager)}, m_object_manager{std::move(other.m_object_manager)},
    m_collision_manager{std::move(other.m_collision_manager)}, m_window{std::move(other.m_window)},
    m_renderer{std::move(other.m_renderer)}, m_main_camera{std::move(other.m_main_camera)}
{

}

SystemManager& SystemManager::operator=(const SystemManager& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

SystemManager& SystemManager::operator=(SystemManager&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_resource_manager = std::move(other.m_resource_manager);
        m_object_manager = std::move(other.m_object_manager);
        m_collision_manager = std::move(other.m_collision_manager);
        m_window = std::move(other.m_window);
        m_renderer = std::move(other.m_renderer);
        m_main_camera = std::move(other.m_main_camera);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Methods
void SystemManager::Input(const SDL_Event& event)
{
    m_object_manager.Input(event);
}
void SystemManager::Logic(float delta_time)
{
    m_object_manager.Logic(delta_time);
}
void SystemManager::FixedLogic(float fixed_delta_time)
{
    m_object_manager.FixedLogic(fixed_delta_time);
    m_collision_manager.FixedLogic(fixed_delta_time);
}
void SystemManager::Render(float delta_time)
{
    m_main_camera.ClearCamera();//clear screen

    m_object_manager.Render(delta_time);

    m_main_camera.Render(delta_time);//render final render image

    //render any debug visuals
    DebugRender::Instance()->RenderQueue();
}

void SystemManager::DestroyElements()
{
    if(m_object_manager.HasObjectsToDestroy())
        m_object_manager.DestroyMarked();

    m_object_manager.HasObjectsToDestroy(false);
}

void SystemManager::Clear()
{
    m_object_manager.Clear();
    m_collision_manager.Clear();
    m_resource_manager.Clear();
    m_main_camera.ClearCamera();//clear screen
}
//</f> /Methods

//<f> Getters/Setters
ResourceManager* SystemManager::Resources() { return &m_resource_manager; }
ObjectManager* SystemManager::Objects() { return &m_object_manager; }
CollisionManager* SystemManager::Colliders() { return &m_collision_manager; }
SDL_Window* SystemManager::Window() const { return m_window; }
SDL_Renderer* SystemManager::Renderer() const { return m_renderer; }
Camera* SystemManager::MainCamera() { return &m_main_camera; }
//</f> /Getters/Setters

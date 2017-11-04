#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include "object_manager.hpp"
#include "collision_manager.hpp"
#include "resource_manager.hpp"
#include "camera.hpp"
#include "SDL.h"

class SystemManager
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        SystemManager(SDL_Window* window, SDL_Renderer* renderer_ptr);
        /** brief Default destructor */
        virtual ~SystemManager() noexcept;

        /** brief Copy constructor */
        SystemManager(const SystemManager& other);
        /** brief Move constructor */
        SystemManager(SystemManager&& other) noexcept;

        /** brief Copy operator */
        SystemManager& operator= (const SystemManager& other);
        /** brief Move operator */
        SystemManager& operator= (SystemManager&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Methods
        void Input(const SDL_Event& event);
        void Logic(float delta_time);
        void FixedLogic(float fixed_delta_time);
        void Render(float delta_time);
        void DestroyElements();
        /**
         * \brief clear the content from the managers
         */
        void Clear();
        //</f> /Methods

        //<f> Getters/Setters
        ResourceManager* Resources();
        ObjectManager* Objects();
        CollisionManager* Colliders();
        SDL_Window* Window() const;
        SDL_Renderer* Renderer() const;
        Camera* MainCamera();
        //</f> /Getters/Setters

    private:
        ResourceManager m_resource_manager;
        ObjectManager m_object_manager;
        CollisionManager m_collision_manager;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        Camera m_main_camera;
};

#endif //SYSTEM_MANAGER_HPP

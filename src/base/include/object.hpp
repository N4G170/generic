#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "behaviour_script.hpp"
#include "render_script.hpp"
#include "collider.hpp"
#include "camera.hpp"
#include "transform.hpp"
#include <functional>
#include <memory>
#include <vector>
#include "uid.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <iostream>

class ObjectManager;

class Object
{
    public:
        //<f> Constructors & operator=
        explicit Object(ObjectManager*);
        ~Object() noexcept;

        Object(const Object& other);
        Object(Object&& other) noexcept;

        Object& operator=(const Object& other);
        Object& operator=(Object&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Scrip functions
        void Input(const SDL_Event& event);
        void Update(float delta_time);
        void FixedUpdate(float fixed_delta_time);
        void Render(float delta_time);
        //</f> /Scrip functions

        //<f> Script management
        /**
         * \brief Takes ownership of a script and manages it (if we dont have it already and it has no owner)
         * \n(will be stored in a std::unique_ptr so do not delete it)
         * \n Returns true on success, false otherwise
         */
        template<typename T>
        bool AddScript(T* script)
        {
            //try to add a new script
            if(script->Owner() != nullptr)//already has an owner
                return false;

            //check if we already have its type (only if camera or render)
            if(std::is_same<T, RenderScript>::value && !m_render_scripts.empty())
                return false;
            else if(std::is_same<T, Camera>::value && !m_camera_scripts.empty())
                return false;

            //lock access to class vars (lock_guard releases itself when funsction returns)
            std::lock_guard<std::mutex> lock(m_access_mutex);

            //check if exits
            auto result{ std::find_if(std::begin(m_scripts), std::end(m_scripts),
                [script](auto& stored_script)->bool { return script->InstanceID() == stored_script.second->InstanceID(); } ) };

            if(result != std::end(m_scripts))//found it but owner is not set (how??)
            {
                script->Owner(this);//set this object as owner
                return false;
            }

            //add script
            m_scripts.emplace( std::type_index(typeid(T)), std::unique_ptr<Script>(script) );
            script->Owner(this);//set this object as owner

            //store quick pointer
            if(std::is_convertible<T*, BehaviourScript*>::value)
                m_behaviour_scripts.push_back( dynamic_cast<BehaviourScript*>(script));
            else if(std::is_convertible<T*, RenderScript*>::value)
                m_render_scripts.push_back( dynamic_cast<RenderScript*>(script));
            else if(std::is_convertible<T*, Camera*>::value)
                m_camera_scripts.push_back( dynamic_cast<Camera*>(script));
            else if(std::is_convertible<T*, Collider*>::value)
                m_collider_scripts.push_back( dynamic_cast<Collider*>(script));

            return true;
        }

        /**
         *  \brief Relese a script from the object (no longer managed by its std::unique_ptr)
         *  \nand returns its pointer.
         *  \nReturns nullptr if script does not exist
         */
        template<typename T>
        T* ReleaseScript(UID instance_id)
        {
            //lock access to class vars (lock_guard releases itself when funsction returns)
            std::lock_guard<std::mutex> lock(m_access_mutex);

            auto result{ std::find_if(std::begin(m_scripts), std::end(m_scripts), [instance_id](auto& stored_script)->bool { return instance_id == stored_script.second->InstanceID(); } ) };

            if(result != std::end(m_scripts))
            {
                if(result->first == std::type_index(typeid(T)))
                {
                    auto script{result->second.release()};
                    m_scripts.erase(result);
                    script->Owner(nullptr);//remove owner
                    return dynamic_cast<T*>(script);
                }
                return nullptr;
            }

            return nullptr;
        }

        /**
         * \brief Remove a script from the object and delete the pointer.
         */
        void DeleteScript(UID instance_id);

        /**
         * \brief Return a new vector with pointers to all scripts
         */
        std::vector<Script*> AllScripts();

        /**
         * \brief Return pointer to first script of type T
         */
        template<typename T>
        T* GetScript()
        {
            //lock access to class vars (lock_guard releases itself when funsction returns)
            std::lock_guard<std::mutex> lock(m_access_mutex);

            auto values_range{ m_scripts.equal_range(std::type_index(typeid(T))) };

            return values_range.first->second;
        }
        /**
         * \brief Return vector of pointers to all scripts of type T
         */
        template<typename T>
        std::vector<T*> GetScripts()
        {
            //lock access to class vars (lock_guard releases itself when funsction returns)
            std::lock_guard<std::mutex> lock(m_access_mutex);

            std::vector<T*> scripts;
            auto range{ m_scripts.equal_range(std::type_index(typeid(T))) };

            for(auto it{range.first}; it != range.second; ++it)
            {
                scripts.push_back(it->second);
            }

            return scripts;
        }
        //</f> /Script management

        //<f> Get/Set
        UID InstanceID() const;
        Transform* TransformPtr();

        /**
         * \brief Returns if object is enabled on not
         */
        bool Enabled() const;
        void Enabled(bool enabled);

        void Enable();
        void Disable();
        //</f> /Get/Set

        //<f> Tags
        /**
         * \brief Adds a tag to the object, True on success False if tag already exists
         * @param tag [description]
         * \return  [description]
         */
        bool AddTag(const std::string& tag);
        bool HasTag(const std::string& tag);
        /**
         * \brief Removes a tag from the object. True on success and false on failure
         * \nFailure will be, probably, because the tag does not exist
         */
        bool RemoveTag(const std::string& tag);
        //</f> /Tags

        //<f> Destroy
        void Destroy();
        bool MarkedForDestruction() const;
        //</f> /Destroy
    protected:
        UID m_instance_id;
        Transform m_transform;

        bool m_marked_for_destruction;
        ObjectManager* m_object_manager;

        //protect access to scripts
        std::mutex m_access_mutex;

        std::unordered_multimap<std::type_index, std::unique_ptr<Script>> m_scripts;

        //Pointers for quick access to specific type of scripts
        std::vector<BehaviourScript*> m_behaviour_scripts;
        std::vector<Collider*> m_collider_scripts;
        /**
         * \brief Can only have one Render script
         */
        std::vector<RenderScript*> m_render_scripts;
        /**
         * \brief Can only have one Camera script
         */
        std::vector<Camera*> m_camera_scripts;

        bool m_enabled;
        std::vector<std::string> m_tags;

        // void DeleteScriptQuickPointer(UID instance_id);
};

#endif //OBJECT_HPP

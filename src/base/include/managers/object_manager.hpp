#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <vector>
#include <memory>
#include "object.hpp"
#include <mutex>

class ObjectManager
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        ObjectManager();
        /** brief Default destructor */
        virtual ~ObjectManager() noexcept;

        /** brief Copy constructor */
        ObjectManager(const ObjectManager& other);
        /** brief Move constructor */
        ObjectManager(ObjectManager&& other) noexcept;

        /** brief Copy operator */
        ObjectManager& operator= (const ObjectManager& other);
        /** brief Move operator */
        ObjectManager& operator= (ObjectManager&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Object Methods
        void Input(const SDL_Event& event);
        void Logic(float delta_time);
        void FixedLogic(float fixed_delta_time);
        void Render(float delta_time);
        //</f> /Object Methods

        //<f> Object Management
        /**
         * \brief Creates a new empty object and returns a pointer to it
         */
        Object* CreateObject();
        /**
         * \brief Checks if the object with the given UID exists and returns a pointer to it, nullptr otherwise
         */
        Object* FindObject(UID instance_id);
        /**
         * \brief Checks if the object with the given UID exists and returns a pointer to it, while releasing it from this class
         * \n meaning that it will no longer be managed by this manager. nullptr otherwise
         */
        Object* ReleaseObject(UID instance_id);
        /**
         * \brief Deletes the object whith the given UID (if it exists). Return true on success, false otherwise
         */
        bool DeleteObject(UID instance_id);

        /**
         * \brief Delete all objects
         */
        void Clear();
        //</f> /Object Management

        //<f> Getters/Setters
        bool HasObjectsToDestroy() const;
        void HasObjectsToDestroy(bool has_objects_to_destroy);

        void DestroyMarked();
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        /**
         * \brief Flag marking the existence of objects to be destroyed
         */
        bool m_has_objects_to_destroy;
        std::vector<std::unique_ptr<Object>> m_objects;
    private:
};

#endif //OBJECT_MANAGER_HPP

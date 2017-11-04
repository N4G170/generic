#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include "collider.hpp"

class CollisionManager
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        CollisionManager();
        /** brief Default destructor */
        virtual ~CollisionManager() noexcept;

        /** brief Copy constructor */
        CollisionManager(const CollisionManager& other);
        /** brief Move constructor */
        CollisionManager(CollisionManager&& other) noexcept;

        /** brief Copy operator */
        CollisionManager& operator= (const CollisionManager& other);
        /** brief Move operator */
        CollisionManager& operator= (CollisionManager&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Methods
        void AddCollider(Collider* collider);
        void RemoveCollider(UID instance_id);

        void FixedLogic(float fixed_delta_time);

        /**
         * \brief Delete all colliders
         */
        void Clear();
        //</f> /Methods

    protected:
        // vars and stuff
        std::vector<Collider*> m_colliders;
    private:
};

#endif //COLLISION_MANAGER_HPP

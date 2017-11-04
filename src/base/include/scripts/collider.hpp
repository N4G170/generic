#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vector3.hpp"
#include "script.hpp"
#include "structs.hpp"
#include <functional>

class Collider: public Script
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        Collider();
        /** brief Default destructor */
        virtual ~Collider() noexcept;

        /** brief Copy constructor */
        Collider(const Collider& other);
        /** brief Move constructor */
        Collider(Collider&& other) noexcept;

        /** brief Copy operator */
        Collider& operator= (const Collider& other);
        /** brief Move operator */
        Collider& operator= (Collider&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        Vector3<float> ColliderLocalPosition() const;
        void ColliderLocalPosition(const Vector3<float>& position);

        Vector3<float> ColliderScale() const;
        void ColliderScale(const Vector3<float>& scale);

        Bounds<float> GlobalBounds() const;

        Vector3<float> BoundRadiusVector() const;
        //</f> /Getters/Setters

        //<f> Collision
        void CheckCollision(Collider* other);
        //</f> /Collision

        //<f> Callbacks
        std::function<void(Collider*)> OnCollision;
        //</f> /Callbacks

    protected:
        // vars and stuff
        Vector3<float> m_local_position;
        Vector3<float> m_scale;
    private:
};

#endif //COLLIDER_HPP

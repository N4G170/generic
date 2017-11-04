#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "vector3.hpp"
#include "uid.hpp"
#include "structs.hpp"
#include "enums.hpp"
#include "camera.hpp"

class Object;

class Transform
{
    public:
        //<f> Constructors & operator=
        Transform();
        ~Transform() noexcept;

        Transform(const Transform& other);
        Transform(Transform&& other) noexcept;

        Transform& operator=(const Transform& other);
        Transform& operator=(Transform&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Position
        //<f> LocalPosition
        Vector3<float> LocalPosition() const;
        void LocalPosition(const Vector3<float>& local_position);
        void LocalPositionX(float local_position_x);
        void LocalPositionY(float local_position_y);
        void LocalPositionZ(float local_position_z);
        //</f> /LocalPosition

        //<f> GlobalPosition
        Vector3<float> GlobalPosition() const;
        void GlobalPosition(const Vector3<float>& global_position);
        void GlobalPositionX(float global_position_x);
        void GlobalPositionY(float global_position_y);
        void GlobalPositionZ(float global_position_z);
        //</f> /GlobalPosition
        //</f> /Position

        //<f> Scale/Size
        //<f> LocalScale
        Vector3<float> LocalScale() const;
        void LocalScale(const Vector3<float>& local_scale);
        void LocalScaleX(float local_scale_x);
        void LocalScaleY(float local_scale_y);
        void LocalScaleZ(float local_scale_z);
        //</f> /LocalScale

        //<f> GlobalScale
        Vector3<float> GlobalScale() const;
        void GlobalScale(const Vector3<float>& global_scale);
        void GlobalScaleX(float global_scale_x);
        void GlobalScaleY(float global_scale_y);
        void GlobalScaleZ(float global_scale_z);
        //</f> /GlobalScale

        /**
         * \brief Returns Local bounds (uses local_position and local_scale)
         */
        Bounds<float> LocalBounds();
        /**
         * \brief Returns Local bounds (uses local_position and local_scale), ajusted to camera position
         */
        Bounds<float> LocalBounds(Camera* camera);
        /**
         * \brief Gets bounds from self and children and calculates global mins and maxs
         */
        Bounds<float> GlobalBounds();
        /**
         * \brief Gets bounds from self and children and calculates global mins and maxs, ajusted to camera position
         */
        Bounds<float> GlobalBounds(Camera* camera);

        //</f> /Scale/Size

        //<f> Rotation
        //<f> LocalRotation
        Vector3<float> LocalRotation() const;
        void LocalRotation(const Vector3<float>& local_rotation);
        void LocalRotationX(float local_rotation_x);
        void LocalRotationY(float local_rotation_y);
        void LocalRotationZ(float local_rotation_z);
        //</f> /LocalRotation

        //<f> GlobalRotation
        Vector3<float> GlobalRotation() const;
        void GlobalRotation(const Vector3<float>& global_rotation);
        void GlobalRotationX(float global_rotation_x);
        void GlobalRotationY(float global_rotation_y);
        void GlobalRotationZ(float global_rotation_z);
        //</f> /GlobalRotation
        //</f> /Rotation

        //<f> Hierarchy (parents/children)
        void Parent(Transform* parent);
        Transform* Parent() const;

        /**
         * \brief Adds a new child to this transform
         */
        void AddChild(Transform* child);
        /**
         * \brief Removes a child from the transform and returns a pointer to it.
         * \nReturns nullptr if child does not exist
         */
        Transform* RemoveChild(UID id);

        /**
         * \brief Return a ref to the vector hlding all of this transform children
         */
        std::vector<Transform*>* Children();
        //</f> /Hierarchy (parents/children)

        //<f> Ownership & UID
        UID InstanceID() const;

        Object* Owner() const;
        void Owner(Object* owner);
        //</f> /Ownership

        //<f> AnchorType
        AnchorType Anchor() const;
        void Anchor(AnchorType anchor);
        //</f> /AnchorType
    private:
        UID m_instance_id;
        Vector3<float> m_local_position;
        Vector3<float> m_local_scale;
        Vector3<float> m_local_rotation;

        Object* m_owner;
        Transform* m_parent;
        std::vector<Transform*> m_children;

        AnchorType m_anchor_type;
};

//<f> Common Functions
/**
 * \brief Ajusts a position vector to a specific anchor.
 * \nUsed for colliders and rendering
 */
Vector3<float> AjustPositionToAnchor(const Vector3<float>& position, const Vector3<float>& size, AnchorType anchor_type);
//</f> /Common Functions

#endif //TRANSFORM_HPP

#ifndef DROP_HPP
#define DROP_HPP

#include "SDL.h"
#include <functional>

#include "behaviour_script.hpp"
#include "vector3.hpp"
#include "collider.hpp"
#include "system_manager.hpp"
#include "basic_frame_animation.hpp"

class  Drop : public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        explicit Drop(SystemManager* system_manager);
        ~Drop() noexcept;

        Drop(const Drop& other);
        Drop(Drop&& other) noexcept;

        Drop& operator=(const Drop& other);
        Drop& operator=(Drop&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Drop* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Get/Set
        Vector3<float> Velocity() const;
        void Velocity(const Vector3<float>& velocity);

        /**
         * \brief Apply a force to current velocity
         */
        void ChangeVelocity(const Vector3<float>& force);

        void ChangeWindForce(const Vector3<float>& wind);
        //</f> /Get/Set

        //<f> Methods
        void DropHit(Collider* other);
        void ResetDrop();
        void Splash();
        //</f> /Methods
    private:
        Vector3<float> m_velocity;
        Vector3<float> m_wind;

        std::function<void()> m_drop_sound;

        Object* m_splash_object;
        BasicFrameAnimation* m_splash_animation;
};
#endif //DROP_HPP

#ifndef SPACE_ROCK_HPP
#define SPACE_ROCK_HPP

#include "behaviour_script.hpp"
#include "vector3.hpp"
#include "collider.hpp"

class Comet : public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** Default constructor */
        Comet();

        /** Copy constructor */
        Comet (const Comet& other);

        /** Move constructor */
        Comet (Comet&& other) noexcept;/* noexcept needed to enable optimizations in containers */

        /** Destructor */
        ~Comet() noexcept; /* explicitly specified destructors should be annotated noexcept as best-practice */

        /** Copy assignment operator */
        Comet& operator= (const Comet& other);

        /** Move assignment operator */
        Comet& operator= (Comet&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Methods
        void Accelerate(float acceleration);
        void Reset();
        void InfluenceDirection(const Vector3<float>& force);
        Vector3<float> Direction() const;

        void OnCollision(Collider* other);
        //</f> /Methods

    private:
        float m_velocity;
        /**
         * \brief Normalized direction vector
         */
        Vector3<float> m_direction;
        bool m_can_reset;

};

#endif //SPACE_ROCK_HPP

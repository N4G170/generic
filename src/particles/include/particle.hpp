#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "SDL.h"
#include "behaviour_script.hpp"
#include "vector3.hpp"

class Particle: public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        Particle();
        /** brief Default destructor */
        virtual ~Particle() noexcept;

        /** brief Copy constructor */
        Particle(const Particle& other);
        /** brief Move constructor */
        Particle(Particle&& other) noexcept;

        /** brief Copy operator */
        Particle& operator= (const Particle& other);
        /** brief Move operator */
        Particle& operator= (Particle&& other) noexcept;
        //</f>

        //<f> Virtual Methods
        Script* Clone() override;
        void Update(float delta_time) override;
        //</f>

        //<f> Methods
        void Release();
        void Stop();
        void StopAndDestroy();
        //</f>

        //<f> Getters/Setters
        void Config(float ttl, const Vector3<float>& direction, float velocity, float z_rotation, bool in_global_space);

        float TTL() const;
        void TTL(float ttl);

        Vector3<float> Direction() const;
        void Direction(const Vector3<float>& direction);

        float Velocity() const;
        void Velocity(float velocity);

        float Rotation() const;
        void Rotation(float rotation);

        bool GlobalSpace() const;
        void GlobalSpace(bool global_space);
        //</f>

    protected:
        // vars and stuff

    private:
        bool m_released;
        float m_ttl;
        Vector3<float> m_direction;
        float m_velocity;
        // Vector3<float> m_velocity;
        float m_rotation;
        bool m_global_space;
};

#endif //PARTICLE_HPP

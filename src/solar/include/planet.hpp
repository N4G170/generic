#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP

#include "behaviour_script.hpp"
#include "enums.hpp"
#include <vector>
#include "SDL.h"
#include "vector3.hpp"
#include "orbit_render.hpp"

class Planet : public BehaviourScript
{
    public:
        //<f> Constructor & operator=
        Planet();
        ~Planet() noexcept;

        Planet(const Planet& other);
        Planet(Planet&& other) noexcept;

        Planet& operator=(const Planet& other);
        Planet& operator=(Planet&& other) noexcept;
        //</f> /Constructor & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Get/Set
        float AngleStep() const;
        void AngleStep(float angle_step);
        float Perihelion() const;
        void Perihelion(float perihelion);
        float Aphelion() const;
        void Aphelion(float aphelion);

        /**
         * \brief Get the interval at which the orbit updates. The lower the faster it updates
         */
        float OrbitUpdateInterval() const;
        /**
         * \brief Set the interval at which the orbit updates. The lower the faster it updates
         */
        void OrbitUpdateInterval(float interval);

        float Mass() const;
        void Mass(float mass);

        void SetOrbitRender(OrbitRender* orbit_render);
        OrbitRender* GetOrbitRender() const;

        void RotationStep(float rotation_step);
        float RotationStep() const;

        void PositionOffset(const Vector3<float>& position_offset);
        Vector3<float> PositionOffset() const;
        //</f> /Get/Set

        //<f> Orbit
        void RecalculateOrbit();

        Vector3<float> GenerateRadianOrbitStep(float perihelion, float aphelion, float radian_angle);
        Vector3<float> GenerateDegreeOrbitStep(float perihelion, float aphelion, float degree_angle);
        std::vector<Vector3<float>> GenerateFullOrbitRadianStep(float perihelion, float aphelion, float radian_angle_step = 0.318f);//+- 1 degree
        std::vector<Vector3<float>> GenerateFullOrbitDegreeStep(float perihelion, float aphelion, float degree_angle_step = 1.f);
        //</f> /Orbit

    protected:
        //orbit
        Vector3<float> m_current_orbit_step;
        Vector3<float> m_position_offset;
        float m_current_angle;
        float m_angle_step;
        float m_current_orbit_time;
        float m_orbit_update_interval;

        float m_perihelion;
        float m_aphelion;
        float m_mass;

        float m_rotation_angle;
        float m_rotation_step;
        //orbit render
        OrbitRender* m_orbit;
};

#endif //CELESTIAL_BODY_HPP

#ifndef XENO_HPP
#define XENO_HPP

#include "celestial_body.hpp"

class Xeno : public CelestialBody
{
    public:
        Xeno();
        virtual void Move(float fixed_frame_time);
    private:
        float m_rotation_sin;
        float m_rotation_cos;
};

#endif //XENO_HPP

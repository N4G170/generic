#ifndef XENO_HPP
#define XENO_HPP

#include "planet.hpp"

class Xeno// : public Planet
{
    public:
        Xeno();
        virtual void Logic(float fixed_frame_time);
    private:
        float m_rotation_sin;
        float m_rotation_cos;
};

#endif //XENO_HPP

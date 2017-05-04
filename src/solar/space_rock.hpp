#ifndef SPACE_ROCK_HPP
#define SPACE_ROCK_HPP

#include "object.hpp"
#include "vector2.hpp"

class SpaceRock : public Object
{
    public:
        /** Default constructor */
        SpaceRock();

        /** Copy constructor */
        SpaceRock (const SpaceRock& other);

        /** Move constructor */
        SpaceRock (SpaceRock&& other) noexcept;/* noexcept needed to enable optimizations in containers */

        /** Destructor */
        ~SpaceRock() noexcept; /* explicitly specified destructors should be annotated noexcept as best-practice */

        /** Copy assignment operator */
        SpaceRock& operator= (const SpaceRock& other);

        /** Move assignment operator */
        SpaceRock& operator= (SpaceRock&& other) noexcept;

        void Reset();

    private:
        Vector2<float> m_velocity;
};

#endif //SPACE_ROCK_HPP

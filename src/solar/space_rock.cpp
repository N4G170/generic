#include "space_rock.hpp"
#include <algorithm>
#include "random.hpp"
#include "constants.hpp"

/** Default constructor */
SpaceRock::SpaceRock()
{
}

/** Copy constructor */
SpaceRock::SpaceRock (const SpaceRock& other)
{
}

/** Move constructor */
SpaceRock::SpaceRock (SpaceRock&& other) noexcept /* noexcept needed to enable optimizations in containers */
{
}

/** Destructor */
SpaceRock::~SpaceRock() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
{
}

/** Copy assignment operator */
SpaceRock& SpaceRock::operator= (const SpaceRock& other)
{
   SpaceRock tmp(other);         // re-use copy-constructor
   *this = std::move(tmp); // re-use move-assignment
   return *this;
}

/** Move assignment operator */
SpaceRock& SpaceRock::operator= (SpaceRock&& other) noexcept
{
   return *this;
}

void SpaceRock::Reset()
{
    m_transform.PositionX( Random(0, window_width - m_transform.Height()) );
    //the left parameter is negative
    m_transform.PositionY( Random(-1 * m_transform.Height() - window_height, m_transform.Height()) );

    m_velocity.X(Random(5, 200));
    m_velocity.Y(Random(5, 200));
}

#ifndef ENUM_HPP
#define ENUM_HPP

enum CelestialBodies
{
    NONE,
    SUN,
    SUN2,
    MERCURY,
    VENUS,
    TERRA,
    LUNA,
    MARS,
    JUPITER,
    SATURN,
    XENO
};

enum SEARCH_TYPE
{
    QUARTILE = 1,
    OCTILE_NOT_CORNER = 2,
};

enum HEURISTIC_TYPE
{
    MANHATTAN = 1,
    OCTILE = 2,
};

enum DIRECTION
{
    ORTHOGONAL = 1,
    DIAGONAL = 2,
};
#endif //ENUM_HPP

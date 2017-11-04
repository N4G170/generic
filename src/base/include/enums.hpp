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

enum class AnchorType
{
    Top_Left,
    Top_Centre,
    Top_Right,

    Centre_Left,
    Centre_Centre,
    Centre_Right,

    Bottom_Left,
    Bottom_Centre,
    Bottom_Right
};

enum class BoundsPositions
{
    Front_Top_Left,
    Front_Top_Right,
    Front_Bottom_Left,
    Front_Bottom_Right,

    Back_Top_Left,
    Back_Top_Right,
    Back_Bottom_Left,
    Back_Bottom_Right,    
};
#endif //ENUM_HPP

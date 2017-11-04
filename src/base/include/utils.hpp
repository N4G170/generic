#ifndef UTILS_HPP
#define UTILS_HPP

#include "SDL.h"
#include "vector3.hpp"
#include "vector3_utils.hpp"
#include "structs.hpp"

bool PointInsideRect(const SDL_Rect& rect, const int& point_x, const int& point_y);

int Lerp(const int& start, const int& end, const float& t);
float Lerp(const float& start, const float& end, const float& t);
double Lerp(const double& start, const double& end, const double& t);

float RadiansToDegrees(float radians);
float DegreesToRadians(float degrees);

/**
 * \brief Rotate a point in the Z axis at the pivot point. The angle must be in radians
 * \return  New point in the rotated position
 */
template<typename T>
Vector3<T>  Rotate2D(const Vector3<T>& original_point, const Vector3<T>& pivot, float angle)
{
    // x′=xcosθ−ysinθ
    // y′=ycosθ+xsinθ
    auto point{original_point};
    //remove pivot from point
    point -= pivot;
    //get sin and cos of angle
    auto sin{std::sin(angle)};
    auto cos{std::cos(angle)};

    auto new_x = point.X() * cos - point.Y() * sin;
    auto new_y = point.Y() * cos + point.X() * sin;

    point.X( new_x + pivot.X() );
    point.Y( new_y + pivot.Y() );

    return point;
}

//<f> Simple casts
//rect casts
SDL_Rect RectFromFloats(float x, float y, float w, float h);

template<typename T>
SDL_Rect BoundsToSDLRect(const Bounds<T>& bounds)
{
    return { CoordinateToInt(bounds.min_x), CoordinateToInt(bounds.min_y), CoordinateToInt(bounds.max_x - bounds.min_x), CoordinateToInt(bounds.max_y - bounds.min_y) };
}
//</f>

//<f> Simple Collision
template<typename T>
bool PointInsideRect(const Vector3<T>& point, const Vector3<T>& rect_position, const Vector3<T>& rect_size)
{
    return point.X() >= rect_position.X() && point.X() <= rect_position.X() + rect_size.X() && point.Y() >= rect_position.Y() && point.Y() <= rect_position.Y() + rect_size.Y();
}

template <typename T>
bool RectCollision(const Vector3<T>& rect_1_position, const Vector3<T>& rect_1_size, const Vector3<T>& rect_2_position, const Vector3<T>& rect_2_size )
{
    //check if any of rect_1 vertices is inside of rect_2, if true we have a collision
    //top left
    if(PointInsideRect(rect_1_position, rect_2_position, rect_2_size))
        return true;
    //top right
    if(PointInsideRect({rect_1_position.X() + rect_1_size.X(), rect_1_position.Y(), 0}, rect_2_position, rect_2_size))
        return true;
    //bottom left
    if(PointInsideRect({rect_1_position.X(), rect_1_position.Y() + rect_1_size.Y(), 0}, rect_2_position, rect_2_size))
        return true;
    //bottom right
    if(PointInsideRect({rect_1_position.X() + rect_1_size.X(), rect_1_position.Y() + rect_1_size.Y(), 0}, rect_2_position, rect_2_size))
        return true;

    //now check if any of rhs is inside lhs (will only reach here is rhs is inside lhs)
    //top left
    if(PointInsideRect(rect_2_position, rect_1_position, rect_1_size))
        return true;
    //top right
    if(PointInsideRect({rect_2_position.X() + rect_2_size.X(), rect_2_position.Y(), 0}, rect_1_position, rect_1_size))
        return true;
    //bottom left
    if(PointInsideRect({rect_2_position.X(), rect_2_position.Y() + rect_2_size.Y(), 0}, rect_1_position, rect_1_size))
        return true;
    //bottom right
    if(PointInsideRect({rect_2_position.X() + rect_2_size.X(), rect_2_position.Y() + rect_2_size.Y(), 0}, rect_1_position, rect_1_size))
        return true;

    return false;
}

template<typename T, typename U>
bool PointInsideBounds(const Vector3<T>& point, const Bounds<U>& bounds)
{
    return point.X() >= bounds.min_x && point.X() <= bounds.max_x &&
           point.Y() >= bounds.min_y && point.Y() <= bounds.max_y &&
           point.Z() >= bounds.min_z && point.Z() <= bounds.max_z;
}

template <typename T, typename U>
bool BoundsCollision( const Bounds<T>& lhs, const Bounds<U>& rhs)
{
    auto bounds_1{lhs};
    auto bounds_2{rhs};

    for(auto i{0}; i<2; ++i)//at the end of the loop we swap bounds_1 and bounds_2
    {
        //front top left
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Front_Top_Left), bounds_2))
            return true;
        //front top right
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Front_Top_Right), bounds_2))
            return true;
        //front bottom left
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Front_Bottom_Left), bounds_2))
            return true;
        //front bottom right
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Front_Bottom_Right), bounds_2))
            return true;

        //back top left
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Back_Top_Left), bounds_2))
            return true;
        //back top right
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Back_Top_Right), bounds_2))
            return true;
        //back bottom left
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Back_Bottom_Left), bounds_2))
            return true;
        //back bottom right
        if(PointInsideBounds(bounds_1.PointPosition(BoundsPositions::Back_Bottom_Right), bounds_2))
            return true;

        //swap bounds
        bounds_1 = rhs;
        bounds_2 = lhs;
        //if it reaches the second loop rhs is inside lhs
    }

    return false;
}
//</f> /Simple Collision

//<f> Maths
/**
 * \brief Limits the value to the interval between min and max
 * @param value value to be checked
 * @param min   min value of the interval
 * @param max   max value of the interval
 * \return  the final value
 */
template<typename T>
T KeepInInterval(T value, T min, T max)
{
    if(value < min)
        value = min;
    else if(value > max)
        value = max;
    return value;
}

template<typename T>
T MapValueToRange(T value, T original_min, T original_max, T new_min, T new_max)
{
    if(original_max - original_min <= 0 || new_max - new_min <= 0)
        return new_min;

    auto ratio = (value - original_min) / (original_max - original_min);//move range to origin (EX. (0,0)) and calculate ratio

    //apply ratio to new_max(moved to origin) and then reposition the value inside new range (with + new_min, to move the value to the correct range)
    return (new_max - new_min) * ratio + new_min;
}

/**
 * \brief The ratio = (value - original_min) / (original_max - original_min)
 */
template<typename T>
T MapValueToRange(T ratio, T new_min, T new_max)
{
    if(new_max - new_min <= 0)
        return new_min;
    //apply ratio to new_max(moved to origin) and then reposition the value inside new range (with + new_min, to move the value to the correct range)
    return (new_max - new_min) * ratio + new_min;
}

//</f>
#endif //UTILS_HPP

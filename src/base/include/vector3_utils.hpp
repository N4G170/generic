#ifndef VECTOR3_UTILS_HPP
#define VECTOR3_UTILS_HPP

#include "SDL.h"
#include "vector3.hpp"
#include <cmath>

template<typename T>
int CoordinateToInt(T coordinate) { return static_cast<int>( std::round(coordinate) ); }
template<int>
int CoordinateToInt(int coordinate) { return coordinate; }

template<typename T>
SDL_Point Vector3ToSDLPoint(const Vector3<T>& point)
{
    return {CoordinateToInt(point.X()), CoordinateToInt(point.Y())};
}

template<typename T>
SDL_Rect Vectors3ToSDLRect(const Vector3<T>& position, const Vector3<T>& size)
{
    return {CoordinateToInt(position.X()), CoordinateToInt(position.Y()),
            CoordinateToInt(size.X()), CoordinateToInt(size.Y())};
}

#endif//VECTOR3_UTILS_HPP

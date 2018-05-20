#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <type_traits>
#include <string>
#include "vector3.hpp"
#include "enums.hpp"
#include "SDL.h"

template<typename T>
struct Bounds
{
    //check if we initialize the vector with the right values
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Bounds template can only integrals of floating point types");
    T min_x{0}, min_y{0}, min_z{0}, max_x{0}, max_y{0}, max_z{0};

    Bounds(): min_x{0}, min_y{0}, min_z{0}, max_x{0}, max_y{0}, max_z{0} {};
    Bounds(T minx, T miny, T minz, T maxx, T maxy, T maxz): min_x{minx}, min_y{miny}, min_z{minz}, max_x{maxx}, max_y{maxy}, max_z{maxz} {};
    Bounds(const Vector3<T>& position, const Vector3<T>& size): min_x{position.X()}, min_y{position.Y()}, min_z{position.Z()},
        max_x{position.X() + size.X()}, max_y{position.Y() + size.Y()}, max_z{position.Z() + size.Z()} {}

    Vector3<T> Size(){ return {max_x - min_x, max_y - min_y, max_z - min_z}; }

    Vector3<T> PointPosition(BoundsPositions bounds_position = BoundsPositions::Front_Top_Left)
    {
        switch (bounds_position)
        {
            case BoundsPositions::Front_Top_Left:       return {min_x, min_y, min_z}; break;
            case BoundsPositions::Front_Top_Right:      return {max_x, min_y, min_z}; break;
            case BoundsPositions::Front_Bottom_Left:    return {min_x, max_y, min_z}; break;
            case BoundsPositions::Front_Bottom_Right:   return {max_x, max_y, min_z}; break;

            case BoundsPositions::Back_Top_Left:        return {min_x, min_y, max_z}; break;
            case BoundsPositions::Back_Top_Right:       return {max_x, min_y, max_z}; break;
            case BoundsPositions::Back_Bottom_Left:     return {min_x, max_y, max_z}; break;
            case BoundsPositions::Back_Bottom_Right:    return {max_x, max_y, max_z}; break;

            default: return {min_x, min_y, min_z};
        }
    }
};

struct BasicFrame
{
    std::string image_path{};
    bool has_src_rect{false};
    SDL_Rect source_rect{0,0,0,0};

    BasicFrame(const std::string& path, bool has_rect, const SDL_Rect& src_rect) : image_path{path}, has_src_rect{has_rect}, source_rect{src_rect} {}
};

#endif //STRUCTS_HPP

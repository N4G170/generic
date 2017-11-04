#ifndef MAP_STRUCTS_HPP
#define MAP_STRUCTS_HPP

#include <vector>
#include "vector3.hpp"

struct MapStats
{
    std::vector<Vector3<float>> positions{};
    std::vector<float> map_costs{};
    float cell_width{};
    float cell_height{};
    int map_width_cell_count{};
    int map_height_cell_count{};
    float map_width{};
    float map_height{};
};

#endif //MAP_STRUCTS_HPP

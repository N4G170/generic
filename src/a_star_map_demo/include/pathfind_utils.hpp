#ifndef PATHDIND_UTILS_H
#define PATHDIND_UTILS_H

#include <queue>
#include <map>
#include <algorithm>

enum class NeighbourSearchType
{
    QUARTILE,
    OCTILE_NO_CORNER_CUT,
    OCTILE_CORNER_CUT
};

struct Neightbour
{
    /**
     * \brief Index of map node neighbour
     */
    int index{0};
    /**
     * \brief Cost of moving to neighbour. Precalculated because of diagonals
     */
    float cost{0};

    Neightbour(int i, float c): index{i}, cost{c}{}
};

//<f> Heuristics
float Dijkstra(const int& delta_x = 0, const int& delta_y = 0, const float& line_cost = 0, const float& diagonal_cost = 0, const int& start_delta_x = 0, const int& start_delta_y = 0)
{
    return 0;
}

float Manhattan(const int& delta_x, const int& delta_y, const float& line_cost, const float& diagonal_cost = 0, const int& start_delta_x = 0, const int& start_delta_y = 0)
{
    return (std::abs(delta_x) + std::abs(delta_y)) * line_cost;
}

float Octile(const int& delta_x, const int& delta_y, const float& line_cost, const float& diagonal_cost, const int& start_delta_x, const int& start_delta_y)
{
    int delta_x_abs = std::abs(delta_x);
    int delta_y_abs = std::abs(delta_y);
    //return (line_cost * (delta_x + delta_y) + (diagonal_cost - 2 * line_cost) * std::min(delta_x, delta_y));

    float heuristics = (line_cost * (delta_x_abs + delta_y_abs) + (diagonal_cost - 2 * line_cost) * std::min(delta_x_abs, delta_y_abs));

    //this last value addition needs to be very, but very small or A* will degrade to best-first and fail some tests
    //0.000001 is used because the vectors are not normalized (sqrt is too expensive here)
    return heuristics + std::abs(delta_x * start_delta_y - start_delta_x * delta_y) * 0.000001;//cross product
}
//</f>

/**
    \brief Extract the X coordinate from the row-major array index
*/
int GetCoordinateX(const int& index, const int& map_width){ return index % map_width; }
/**
    \brief Extract the Y coordinate from the row-major array index
*/
int GetCoordinateY(const int& index, const int& map_width){ return index / map_width; }
/**
    \brief Calculate the row-major array index of a given x, y pair
*/
int GetIndexFromCoordinates(const int& x, const int& y, const int& map_width){ return y * map_width + x; }

/**
    \brief Checks if a given node position is passable or not (invalid positions are marked as impassable)
*/
const bool IsPassable(const int& x, const int& y, const int& map_width, const int& map_height, const float* map)
{
    int index = y * map_width + x;
    return x >= 0 && x < (map_width) && y >= 0 && y < (map_height) && map[index] >= 1;//passable
}

/**
\brief This function can be made generic for other container types
*/
template< typename T, typename U>
U GetMapValue(std::map<T,U>& container, const T& key, const U& default_value)
{
    auto search = container.find(key);
    if(search == container.end())//if the key does not exist, create it and set default value
        container[key] = default_value;
    return container[key];
}

std::queue<Neightbour> GetNeighbors(const int& current_index, const int& map_width, const int& map_height, const float* map, NeighbourSearchType search_type = NeighbourSearchType::QUARTILE)
{
    std::queue<Neightbour> neighbours;

    //check adjacent cells
    unsigned short current_node_y = GetCoordinateY(current_index, map_width);
    unsigned short current_node_x = GetCoordinateX(current_index, map_width);

    bool has_north{false}, has_south{false};
    bool has_east{false}, has_west{false};

    bool has_nw{false}, has_ne{false};
    bool has_sw{false}, has_se{false};

    //up
    if(IsPassable(current_node_x, current_node_y - 1, map_width, map_height, map))//has row above
    {
        auto index{GetIndexFromCoordinates(current_node_x, current_node_y - 1, map_width)};
        Neightbour neighbour{index, map[index] };
        neighbours.push(neighbour);//move one up
        has_north = true;
    }
    //down
    if(IsPassable(current_node_x, current_node_y + 1, map_width, map_height, map))//has row bellow
    {
        auto index{GetIndexFromCoordinates(current_node_x, current_node_y + 1, map_width)};
        Neightbour neighbour{index, map[index] };
        neighbours.push(neighbour);//move one down
        has_south = true;
    }
    //left
    if(IsPassable(current_node_x - 1, current_node_y, map_width, map_height, map))//has left
    {
        auto index{GetIndexFromCoordinates(current_node_x - 1, current_node_y, map_width)};
        Neightbour neighbour{index, map[index] };
        neighbours.push(neighbour);//move one left
        has_west = true;
    }
    //right
    if(IsPassable(current_node_x + 1, current_node_y, map_width, map_height, map))//has right
    {
        auto index{GetIndexFromCoordinates(current_node_x + 1, current_node_y, map_width)};
        Neightbour neighbour{index, map[index] };
        neighbours.push(neighbour);//move one right
        has_east = true;
    }

    if(search_type == NeighbourSearchType::QUARTILE)
        return neighbours;

    //get diagonals with no corner cut
    has_ne = has_north && has_east;
    has_nw = has_north && has_west;
    has_se = has_south && has_east;
    has_sw = has_south && has_west;

    float diagonal_modifier{1.4142135623730950488f};

    if(has_ne && IsPassable(current_node_x + 1, current_node_y - 1,  map_width, map_height, map))
    {
        auto index{GetIndexFromCoordinates(current_node_x + 1, current_node_y - 1, map_width)};
        Neightbour neighbour{index, map[index] * diagonal_modifier};
        neighbours.push(neighbour);
    }

    if(has_nw && IsPassable(current_node_x - 1, current_node_y - 1,  map_width, map_height, map))
    {
        auto index{GetIndexFromCoordinates(current_node_x - 1, current_node_y - 1, map_width)};
        Neightbour neighbour{index, map[index] * diagonal_modifier};
        neighbours.push(neighbour);
    }

    if(has_se && IsPassable(current_node_x + 1, current_node_y + 1,  map_width, map_height, map))
    {
        auto index{GetIndexFromCoordinates(current_node_x + 1, current_node_y + 1, map_width)};
        Neightbour neighbour{index, map[index] * diagonal_modifier};
        neighbours.push(neighbour);
    }

    if(has_sw && IsPassable(current_node_x - 1, current_node_y + 1,  map_width, map_height, map))
    {
        auto index{GetIndexFromCoordinates(current_node_x - 1, current_node_y + 1, map_width)};
        Neightbour neighbour{index, map[index] * diagonal_modifier};
        neighbours.push(neighbour);
    }

    return neighbours;
}
#endif //PATHDIND_UTILS_H

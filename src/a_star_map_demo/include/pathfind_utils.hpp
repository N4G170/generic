#ifndef PATHDIND_UTILS_H
#define PATHDIND_UTILS_H

#include <queue>
#include <map>
#include <algorithm>

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
int GetIndexFromCoordinate(const int& x, const int& y, const int& map_width){ return y * map_width + x; }

/**
    \brief Checks if a given node position is passable or not (invalid positions are marked as impassable)
*/
const bool IsPassable(const int& x, const int& y, const int& map_width, const int& map_height, const unsigned char* map)
{
    int index = y * map_width + x;
    return x >= 0 && x < (map_width) && y >= 0 && y < (map_height) && map[index] == 1;//passable
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

std::queue<int> GetNeighbors(const int& current_index, const int& map_width, const int& map_height, const unsigned char* map)
{
    std::queue<int> neighbors;

    //check adjacent cells
    unsigned short current_node_y = GetCoordinateY(current_index, map_width);
    unsigned short current_node_x = GetCoordinateX(current_index, map_width);

    //up
    if(IsPassable(current_node_x, current_node_y - 1, map_width, map_height, map))//has row above
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x, current_node_y - 1, map_width));//move one up
    }
    //down
    if(IsPassable(current_node_x, current_node_y + 1, map_width, map_height, map))//has row bellow
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x, current_node_y + 1, map_width));//move one down
    }
    //left
    if(IsPassable(current_node_x - 1, current_node_y, map_width, map_height, map))//has left
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x - 1, current_node_y, map_width));//move one left
    }
    //right
    if(IsPassable(current_node_x + 1, current_node_y, map_width, map_height, map))//has right
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x + 1, current_node_y, map_width));//move one right
    }

    return std::move(neighbors);
}
#endif //PATHDIND_UTILS_H

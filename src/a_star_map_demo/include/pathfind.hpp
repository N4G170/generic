#ifndef PATHFIND_H
#define PATHFIND_H

#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <bitset>
#include <vector>

#include "pathfind_utils.hpp"
#include <chrono>

using namespace std::chrono_literals;

//helper struct
struct Node
{
    int index = 0;
    float g_cost;//"real" cost from start to this node
    float f_cost;//"fake" cost to target ( g + h)
    float h_cost;//heuristic cost

    Node(){}

    Node(int new_index, float new_g_cost, float new_h_cost):index{new_index}, g_cost{new_g_cost}, h_cost{new_h_cost}
    {
        f_cost = g_cost + new_h_cost;
    }

    bool operator() (const Node& left_node, const Node& right_node) const//used by multiset
    {
        return left_node.f_cost < right_node.f_cost;// && left_node.h_cost < right_node.h_cost;// || left_node.insertion_id > right_node.insertion_id;
    }
};


//given assumptions
// 1 - 1≤nMapWidth,data.map_height
// 2 - 0≤nStartX,nTargetX<nMapWidth
// 3 - 0≤nStartY,nTargetY<nMapHeight
// 4 - Both Start and Target are empty locations,
// 5 - nOutBufferSize≥0

std::vector<int> FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
             const float* pMap, const int nMapWidth, const int nMapHeight, NeighbourSearchType search_type = NeighbourSearchType::QUARTILE)

{
    std::vector<int> path_indeces;
    int start_index = GetIndexFromCoordinates( nStartX, nStartY, nMapWidth);
    int target_index = GetIndexFromCoordinates( nTargetX, nTargetY, nMapWidth);
    int map_length = nMapWidth * nMapHeight;

    //will keep the nodes ordered by cost(ascending order). The second "Node" in the template is used to set the compare function to the struct defined operator()
    std::multiset<Node, Node> to_visit;//cost is the key and the value is the index
    std::map<int, bool> open_nodes;//keeps record if a node is open
    std::map<int, bool> closed_nodes;//keeps record if a node is open
    std::map<int, int> parents;//parent cells for each cell
    std::map<int, float> g_costs;//cost of moving to a cell

    //movement costs
    float line_cost {1};
    std::queue<Neightbour> neighbours_queue;

    //Start path find
    Node current_node{start_index, 0, Manhattan( nTargetX - nStartX, nTargetY - nStartY, line_cost )};//base cost of start is 0
    to_visit.insert(current_node);//inserts the first cell in the set so we can start searching
    parents[start_index] = -1;//the start cell has no parent

    while(to_visit.size() > 0)//we have elements to check
    {
        //get the cell with lowest cost
        current_node = *to_visit.begin();

        //remove the first cell as we are processing it
        to_visit.erase(to_visit.begin());

        //mark as closed
        closed_nodes[current_node.index] = true;

        if(current_node.index == target_index)//found target
        {
            path_indeces.push_back(current_node.index);//store target node
            int parent_index = parents[current_node.index];//get current node parent from paretns map

            while(parent_index > -1)
            {
                path_indeces.push_back(parent_index);//store parent node
                parent_index = parents[parent_index];//get next parent
            }

            std::reverse(std::begin(path_indeces), std::end(path_indeces));

            return path_indeces;//found path
        }

        neighbours_queue = GetNeighbors(current_node.index, nMapWidth, nMapHeight, pMap, search_type);

        while(neighbours_queue.size() > 0)
        {
            auto neighbour = neighbours_queue.front();
            neighbours_queue.pop();//remove first

            if( closed_nodes[neighbour.index] )//node already closed
                continue;

            int x = GetCoordinateX(neighbour.index, nMapWidth);
            int y = GetCoordinateY(neighbour.index, nMapWidth);

            //calculate the g_cost to neighbour from current node
            float new_neighbour_g_cost = g_costs[current_node.index] + neighbour.cost;
            // float new_neighbour_g_cost = g_costs[current_node.index] + pMap[neighbour.index];

            if(!open_nodes[neighbour.index] || new_neighbour_g_cost < GetMapValue<int, float>(g_costs, neighbour.index, map_length) )//new node or one with lower g_cost
            {
                g_costs[neighbour.index] = new_neighbour_g_cost;//set new cost
                parents[neighbour.index] = current_node.index;

                Node new_node{ neighbour.index, new_neighbour_g_cost,
                    Manhattan( nTargetX - x, nTargetY - y, line_cost ) };

                if(!open_nodes[neighbour.index])//add new to open set
                {
                    to_visit.insert(new_node);
                    open_nodes[neighbour.index] = true;
                }
                else//update node in the set
                {
                    //custom condition find
                    auto search_result = std::find_if(to_visit.begin(), to_visit.end(),
                    [&neighbour](const Node& stored_node)
                    {
                        return stored_node.index == neighbour.index;
                    });

                    if(search_result != to_visit.end())//found item
                    {
                        to_visit.erase(search_result);//remove old
                        to_visit.insert(new_node);//insert updated node
                    }
                }
            }
        }//while(neighbours_queue.size() > 0)

    }//while not empty

    return path_indeces;
}

#endif //PATHFIND_H

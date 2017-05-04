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

#include "pathfind_utils.hpp"
#include "message_writer.hpp"

using namespace std::chrono_literals;

//helper struct
struct Node
{
    int index = 0;
    float g_cost;
    float f_cost;
    float h_cost;

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

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)

{
    int start_index = GetIndexFromCoordinate( nStartX, nStartY, nMapWidth);
    int target_index = GetIndexFromCoordinate( nTargetX, nTargetY, nMapWidth);
    int map_length = nMapWidth * nMapHeight;

    //will keep the nodes ordered by cost(ascending order). The second "Node" in the template is used to set the compare function to the struct defined operator()
    std::multiset<Node, Node> to_visit;//cost is the key amd the value is the index
    std::map<int, bool> open_nodes;//keeps record if a node is open
    std::map<int, bool> closed_nodes;//keeps record if a node is open
    std::map<int, int> parents;//parent cells for each cell
    std::map<int, float> g_costs;//cost of moving to a cell

    //movement costs
    float line_cost {1};
    std::vector<float> movement_cost { 0, 1, 2, 1, 1, 1000, 1000 ,1 };//these values are ordered based on the cell type id (the first value is just there to increase the index for all others)
    std::queue<int> neighbors_queue;

    float min_path_cost{-1};

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

        if(current_node.index == target_index)
        {
            pOutBuffer[0] = current_node.index;//store target node
            int parent_index = parents[current_node.index];//get current node parent from paretns map
            min_path_cost = g_costs[current_node.index];//get cost to get to target

            if(min_path_cost > nOutBufferSize)
            {
                return -2;//buffer is too small
            }

            for(int i{1}; i < min_path_cost; i++)// index 0 was added before
            {
                pOutBuffer[i] = parent_index;//store parent node
                parent_index = parents[parent_index];//get next parent
            }

            for(int i{0}, j = min_path_cost-1; i < min_path_cost/2; i++, j--)
                std::swap( pOutBuffer[i], pOutBuffer[j] );

            MessageWriter::Instance()->WriteLineToConsole("Pathfinder - Path found, with length " + std::to_string(min_path_cost));

            return min_path_cost;//found path
        }

        neighbors_queue = GetNeighbors(current_node.index, nMapWidth, nMapHeight, pMap);

        while(neighbors_queue.size() > 0)
        {
            auto neighbor = neighbors_queue.front();
            neighbors_queue.pop();//remove first

            if( closed_nodes[neighbor] )
                continue;

            int x = GetCoordinateX(neighbor, nMapWidth);
            int y = GetCoordinateY(neighbor, nMapWidth);

            //calculate the g_cost to neighbor from current node
            float new_neighbor_g_cost = g_costs[current_node.index] + movement_cost[pMap[neighbor]];

            if(!open_nodes[neighbor] || new_neighbor_g_cost < GetMapValue<int, float>(g_costs, neighbor, map_length))//new node or one with lower g_cost
            {
                g_costs[neighbor] = new_neighbor_g_cost;//set new cost
                parents[neighbor] = current_node.index;

                Node new_node{ neighbor, new_neighbor_g_cost,
                    Manhattan( nTargetX - x, nTargetY - y, line_cost ) };

                if(!open_nodes[neighbor])//add new to open set
                {
                    to_visit.insert(new_node);
                    open_nodes[neighbor] = true;
                }
                else//update node in the set
                {
                    //custom condition find
                    auto search_result = std::find_if(to_visit.begin(), to_visit.end(),
                    [&neighbor](const Node& stored_node)
                    {
                        return stored_node.index == neighbor;
                    });

                    if(search_result != to_visit.end())//found item
                    {
                        to_visit.erase(search_result);//remove old
                        to_visit.insert(new_node);//insert updated node
                    }
                }
            }
        }//while(neighbors_queue.size() > 0)

    }//while not empty

    MessageWriter::Instance()->WriteLineToConsole("Pathfinder - Failed to find path.");

    return -1;
}

#endif //PATHFIND_H

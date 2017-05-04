#ifndef GRAPH
#define GRAPH

#include <vector>
#include <memory>
#include "graph_node.hpp"

template<typename T>
class Graph
{
    public:
        Graph();
        virtual ~Graph() noexcept;

        Graph(const Graph& other);
        Graph(Graph&& other) noexcept;

        Graph& operator=(const Graph& other);
        Graph& operator=(Graph&& other) noexcept;

    private:
        std::vector<std::unique_ptr<GraphNode<T>>> nodes;
};

#endif //GRAPH

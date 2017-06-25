#include "graph_node.hpp"
#include <utility>

template<typename T>
GraphNode<T>::GraphNode():m_data{nullptr}
{

}

template<typename T>
GraphNode<T>::~GraphNode() noexcept
{

}

template<typename T>
GraphNode<T>::GraphNode(const GraphNode& other):m_data{other.m_data}, m_nodes{other.m_nodes}
{
    
}

template<typename T>
GraphNode<T>::GraphNode(GraphNode&& other) noexcept
{

}

template<typename T>
GraphNode<T>& GraphNode<T>::operator= (const GraphNode& other)
{
    GraphNode tmp = GraphNode(other);
    *this = std::move(tmp);
    return *this;
}

template<typename T>
GraphNode<T>& GraphNode<T>::operator= (GraphNode&& other) noexcept
{

    return *this;
}

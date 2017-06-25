#ifndef GRAPH_NODE
#define GRAPH_NODE

#include <vector>
#include <memory>

template<typename T>
class GraphNode
{
    public:
        GraphNode();
        explicit GraphNode(T* data);
        virtual ~GraphNode() noexcept;

        GraphNode(const GraphNode& other);
        GraphNode(GraphNode&& other) noexcept;

        GraphNode& operator=(const GraphNode& other);
        GraphNode& operator=(GraphNode&& other) noexcept;

        T* Data();
        void Data(T* data);

    private:
        std::vector<std::shared_ptr<GraphNode>> m_nodes;
        T* m_data;
};

#endif //GRAPH_NODE

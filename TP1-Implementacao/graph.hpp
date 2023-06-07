#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph {
public:
    Graph(int num_vertices);
    void add_aresta(int u, int v, int w);
    int getNumVertices() const;
    const std::vector<std::pair<int, int>>& getAdjList(int u) const;

private:
    int num_vertices_;
    std::vector<std::vector<std::pair<int, int>>> adj_list_;
};

#endif // GRAPH_HPP
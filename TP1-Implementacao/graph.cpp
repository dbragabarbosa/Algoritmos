#include "graph.hpp"
#include <iostream>

using namespace std;

Graph::Graph(int num_vertices) : num_vertices_(num_vertices), adj_list_(num_vertices) 
{

}

void Graph::add_aresta(int u, int v, int w) 
{
    adj_list_[u].push_back({v, w});
    adj_list_[v].push_back({u, w});
}

int Graph::getNumVertices() const 
{
    return num_vertices_;
}

const std::vector<std::pair<int, int>>& Graph::getAdjList(int u) const 
{
    return adj_list_[u];
}
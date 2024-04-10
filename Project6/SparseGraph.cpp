#include "SparseGraph.h"
#include <stdexcept>
#include <vector>
const int DEFAULT = 10;

using namespace std;

SparseGraph::SparseGraph(void) : \
    Graph(DEFAULT, 0), adj_list(DEFAULT) {}

SparseGraph::SparseGraph(const int V, const int E) : \
    Graph(V, E), adj_list(V) {}

SparseGraph::SparseGraph(const SparseGraph &other) : \
    Graph(other.V, other.E), adj_list(other.adj_list) {}

SparseGraph::~SparseGraph() {
    
}

SparseGraph& SparseGraph::operator=(const SparseGraph &other) {
    if (this != &other) {
        V = other.V;
        E = other.E;
        adj_list = other.adj_list;
    }
    return *this;
}

bool SparseGraph::isEdge( int v1,  int v2)const {
    if (v1 >= V or v2 >= V or v1 < 0 or v2 < 0)
        throw invalid_argument("isEdge - Invalid Vertices");
    
    for (const auto& edge : adj_list[v1]) {
        
        if (edge.first == v2)
            return true;
    }
    return false;
}

int SparseGraph::getWeight( int v1,  int v2)const {
    if (v1 >= V or v2 >= V or v1 < 0 or v2 < 0)
        throw invalid_argument("getWeight - Invalid Vertices");
    if (!isEdge(v1,v2)) return -1;

    int w = -1;
    for (const auto& edge : adj_list[v1]) {
        if (edge.first == v2) {
            w = edge.second;
            break;
        }
    }
    return w;
}

void SparseGraph::insertEdge( int v1,  int v2, int w) {
    if (v1 >= V or v2 >= V or v1 < 0 or v2 < 0)
        throw invalid_argument("insertEdge - Invalid Vertices");
    if (w < 0) throw invalid_argument("insertEdge - Invalid Weight");
    
    adj_list[v1].emplace_back(v2, w);

    #ifndef DIRECTED_GRAPH
    adj_list[v2].emplace_back(v1, w);
    #endif
}
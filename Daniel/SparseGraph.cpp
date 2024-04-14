#include "SparseGraph.h"
#include <stdexcept>
#include <limits>
#include <queue>

SparseGraph::SparseGraph(void) : \
    Graph(DEFAULT, 0), adj_list(DEFAULT) {}

SparseGraph::SparseGraph(const int V, const int E) : \
    Graph(V, E), adj_list(V) {}

SparseGraph::SparseGraph(const SparseGraph &other) : \
    Graph(other.vert_count, other.edge_count), adj_list(other.adj_list) {}

SparseGraph& SparseGraph::operator=(const SparseGraph &other) {
    if (this != &other) {
        vert_count = other.vert_count;
        edge_count = other.edge_count;
        adj_list = other.adj_list;
    }
    return *this;
}

bool SparseGraph::isEdge(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("isEdge - Invalid Vertices");

    for (const auto& edge : adj_list[v1]) {
        if (edge.first == v2)
            return true;
    }
    return false;
}

int SparseGraph::getWeight(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("getWeight - Invalid Vertices");
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

void SparseGraph::insertEdge(const int v1, const int v2, int w) {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("insertEdge - Invalid Vertices");
    if (w < 0) 
        throw std::invalid_argument("insertEdge - Invalid Weight");

    adj_list[v1].emplace_back(v2, w);

    #ifndef DIRECTED_GRAPH
    adj_list[v2].emplace_back(v1, w);
    #endif
}

void SparseGraph::BFS(int source) {
    if (source < 0 or source > vert_count - 1)
        throw std::invalid_argument("BFS - source out of range");

    table["color"].assign(vert_count, 0); //0: W, 1: G, 2: B
    table["dist"].assign(vert_count, std::numeric_limits<int>::infinity());
    table["pred"].assign(vert_count, -1); //-1: NIL

    table["color"][source] = 1;
    table["dist"][source] = 0;
    table["pred"][source] = -1;

    std::queue<int> Q;
    Q.push(source);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (const auto& edge : adj_list[u]) {
            if (table["color"][edge.first] == 0) {
                table["color"][edge.first] = 1;
                table["dist"][edge.first] = table["dist"][u] + 1;
                table["pred"][edge.first] = u;
                Q.push(edge.first);
            }
        }
        table["color"][u] = 2;
    }
}

void SparseGraph::DFS(void) {
    dfs_edges.clear();

    table["color"].assign(vert_count, 0); //0: W, 1: G, 2: B
    table["pred"].assign(vert_count, -1); //-1: NIL
    table["disc"].assign(vert_count, -1);
    table["f"].assign(vert_count, -1);

    int time = 0;
    for (size_t i=0; i < vert_count; ++i) {
        if (table["color"][i] == 0)
            DFS_Visit(i, time);
    }
}

void SparseGraph::DFS_Visit(int v, int &clock) {
    clock++;

    table["disc"][v] = clock;
    table["color"][v] = 1;

    for (const auto& edge : adj_list[v]) {
        dfs_edges.emplace_back(std::make_pair(v, edge.first));

        if (table["color"][edge.first] == 0) {
            table["pred"][edge.first] = v;
            DFS_Visit(edge.first, clock);
        }
    }
    clock++;
    table["f"][v] = clock;
    table["color"][v] = 2;
}
#include "DenseGraph.h"

DenseGraph::DenseGraph(void) : \
    Graph(DEFAULT, 0), matrix(DEFAULT, std::vector<int>(DEFAULT, -1)) {}

DenseGraph::DenseGraph(const int V, const int E) : \
    Graph(V, E), matrix(V, std::vector<int>(V, -1)) {}

DenseGraph::DenseGraph(const DenseGraph &other) : \
    Graph(other.vert_count, other.edge_count), matrix(other.matrix) {}

DenseGraph& DenseGraph::operator=(const DenseGraph &other) {
    if (this != &other) {
        vert_count = other.vert_count;
        edge_count = other.edge_count;
        matrix = other.matrix;
    }
    return *this;
}

bool DenseGraph::isEdge(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("isEdge - Invalid Vertices");

    return matrix[v1][v2] >= 0;
}

int DenseGraph::getWeight(const int v1, const int v2) const {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("getWeight - Invalid Vertices");
    if (!isEdge(v1,v2)) return -1;

    return matrix[v1][v2];
}

void DenseGraph::insertEdge(const int v1, const int v2, int w) {
    if (v1 >= vert_count or v2 >= vert_count or v1 < 0 or v2 < 0)
        throw std::invalid_argument("insertEdge - Invalid Vertices");
    if (w < 0) 
        throw std::invalid_argument("insertEdge - Invalid Weight");

    if (matrix[v1][v2] == -1) {
        matrix[v1][v2] = w;

        #ifndef DIRECTED_GRAPH
        matrix[v2][v1] = w;
        #endif
    }
}

void DenseGraph::BFS(int source) {
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

        for (int i=0; i < vert_count; ++i) {
            if (table["color"][i] == 0 and isEdge(u, i)) {
                table["color"][i] = 1;
                table["dist"][i] = table["dist"][u] + 1;
                table["pred"][i] = u;
                Q.push(i);
            }
        }
        table["color"][u] = 2;
    }
} 

void DenseGraph::DFS(void) {
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

void DenseGraph::DFS_Visit(int v, int &clock) {
    clock++;

    table["disc"][v] = clock;
    table["color"][v] = 1;
    
    for (int i=0; i < vert_count; ++i) {
        if (isEdge(v, i)) {
            dfs_edges.emplace_back(std::make_pair(v, i));

            if (table["color"][i] == 0) {
                table["pred"][i] = v;
                DFS_Visit(i, clock);
            }
        }
    }
    clock++;
    table["f"][v] = clock;
    table["color"][v] = 2;
}
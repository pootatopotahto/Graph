#include "Graph.h"

#ifndef DENSEGRAPH_H
#define DENSEGRAPH_H

class DenseGraph : public Graph {
    private:
        std::vector<std::vector<int>> matrix;
    public:
        DenseGraph(void);
        DenseGraph(const int V, const int E);
        DenseGraph(const DenseGraph &other);

        DenseGraph& operator=(const DenseGraph &other);

        void insertEdge(const int v1, const int v2, int w) override;
        bool isEdge(const int v1, const int v2) const override;
        int getWeight(const int v1, const int v2) const override;

        //BFS-based Algorithms
        void BFS(int source) override;

        //DFS-based Algorithms
        void DFS(void) override;
        void DFS_Visit(int v, int &clock) override;
};

#endif
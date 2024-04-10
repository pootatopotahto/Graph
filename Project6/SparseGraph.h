#include "Graph.h"
#include <utility>
#include <list>
#include <vector>

using namespace std;

#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

class SparseGraph : public Graph {
    private:
        vector<list<pair<int,int>>> adj_list;
    public:
        SparseGraph     (void);
        SparseGraph     (const int V, const int E);
        SparseGraph     (const SparseGraph &other);
        ~SparseGraph    (void); 

        SparseGraph& operator=      (const SparseGraph &other);

        void insertEdge     ( int v1,  int v2, int w);
        bool isEdge         ( int v1,  int v2) const;
        int getWeight       ( int v1,  int v2) const ;
};

#endif
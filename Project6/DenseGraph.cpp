#include "DenseGraph.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

//===========================================
// Default constructor
// this method creates and initialize a Graph object
// params: none
// return value: none
//===========================================

			DenseGraph::DenseGraph	(void) : Graph()
{
    matrix = new int *[V];
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];

        for (int j =0; j<V; j++)
        {
            matrix[i][j] = -1;
        }
    }
    
}
//===========================================
// Default constructor
// this method creates and initialize a Graph object
// params: vertices, edges
// return value: none
//===========================================
	DenseGraph::DenseGraph	(int vertices, int edges) : Graph(vertices, edges)
{
    matrix = new int *[V];
    for (int i = 0; i < V; i++)
    {
        matrix[i] = new int[V];

        for (int j =0; j<V; j++)
        {
            matrix[i][j] = -1;
        }
    }
    
}
//===========================================
// copy constructor
// this method creates and initialize a Graph object
// params: const Graph &gp
// return value: none
//===========================================
        DenseGraph::DenseGraph            (const DenseGraph &gp) : Graph(gp)
{
    matrix = new int *[V];
    for (int i = 0; i < V; i++){
        matrix[i] = new int[V];
        for(int j = 0; j < V; j++){
            matrix[i][j] = gp.matrix[i][j];
        }
    }
}
//===========================================
// Destructor
// this method deletes the graph
// params: none
// return value: none
//===========================================
        DenseGraph::~DenseGraph      (void)
{
    for (int i = 0; i < V; i++)
        delete []matrix[i];
    delete []matrix;
}

//===========================================
// assignment operator
// this method creates a new densegraph with same vertices 
// and edges and return it
// params: const denseGraph &gp
// return value: Graph
//===========================================
 DenseGraph&   DenseGraph::operator= 	   ( const DenseGraph &gp )
 {
    if(&gp != this){
        Graph::operator=(gp);       // call the graph assignment operator to assign E and V

        for (int i = 0; i < V; i++)
            delete []matrix[i];
        delete []matrix;

        matrix = new int *[V];
        for (int i = 0; i < V; i++){
            matrix[i] = new int[V];
            for(int j = 0; j < V; j++){
                matrix[i][j] = gp.matrix[i][j];
            }
        }
    }
    return *this;
 }

  bool     DenseGraph::isEdge         (int v1, int v2) const
  {
    if ( v1 >= V || v1 < 0 || v2 >= V || v2 < 0)
        throw invalid_argument("isEdge - Invalid Vertices");
    return matrix[v1][v2] >= 0 ;
  }

  int       DenseGraph::getWeight   (int v1, int v2)const
  {
    if ( v1 >= V || v1 < 0 || v2 >= V || v2 < 0)
        throw invalid_argument("getWeight - Invalid Vertices");
    if (!isEdge(v1,v2))
        return -1;
    return matrix[v1][v2];
  }

  void      DenseGraph:: insertEdge (int v1, int v2, int weight)
  {
    if ( v1 >= V || v1 < 0 || v2 >= V || v2 < 0)
        throw invalid_argument("insertEdge - Invalid Vertices");
    if (weight < 0)
        throw invalid_argument("insertEdge - Invalid weight");
    
    matrix[v1][v2] = weight;

    #ifndef DIRECTED_GRAPH
    matrix[v2][v1] = weight;
    #endif
  }
    
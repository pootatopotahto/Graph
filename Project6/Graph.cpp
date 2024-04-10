#include "Graph.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const int DEFAULT = 10;

//===========================================
// Default constructor
// this method creates and initialize a Graph object
// params: none
// return value: none
//===========================================

			Graph::Graph	(void)
{
    V = DEFAULT;
    E = 0;

}
//===========================================
// Default constructor
// this method creates and initialize a Graph object
// params: vertices, edges
// return value: none
//===========================================

            Graph::Graph	( int vertices, int edges)
{
   V = vertices;
   E = edges; 

}
//===========================================
// copy constructor
// this method creates and initialize a Graph object
// params: const Graph &gp
// return value: none
//===========================================
            Graph::Graph     (const Graph &gp) 
{
    V = gp.V;
    E = gp.E;
}
//===========================================
// Destructor
// this method deletes the graph
// params: none
// return value: none
//===========================================
            Graph::~Graph 		        ( void )
{
   
}
//===========================================
// assignment operator
// this method creates a new graph with same vertices 
// and edges and return it
// params: const Graph &gp
// return value: Graph
//===========================================
 Graph&   Graph::operator= 	    ( const Graph &gp )
 {
   

    V = gp.V;
    E = gp.E;

    return *this;

 }
//===========================================
// cin
// this method reads in a graph
// params: istream &is, Graph &gp
// return value:
//===========================================
 istream & operator>> ( istream &is, Graph &gp )
 {
    int v1, v2, weight;
    int E = gp.E;

   for(int i = 0; i < E; i++){
      if (!(is >> v1 >> v2 >> weight))
      {
          if (!is.eof())
            throw runtime_error("Error reading edge data");
         else  
            break;
      }
      //cout << v1 << v2 << weight << endl;
      gp.insertEdge (v1,v2, weight);
      
   }
   return is;
 }
//===========================================
// cout
// this method prints a graph
// params: ostream &os, const Graph &gp
// return value: 
//===========================================
 ostream & operator<< ( ostream &os, const Graph &gp )
 {
   os << "G= (" << gp.V << ", " << gp.E << ") "<< endl;
   for (int i = 0; i< gp.V; i++ ){
      for(int j = 0; j <gp.V; j++){
         if (gp.isEdge(i, j)){
            
            os << i << " " << j << " "<< gp.getWeight(i,j) << endl;
         }
      }
   }
   return os;

 }
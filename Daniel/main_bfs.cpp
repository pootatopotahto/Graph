//================================================================
// Matt Kretchmar
// April 2024
// main_bfs.cpp
// This file assumes the A-level implementation for Project 6
// It calls the functions associated with the BFS search.
//================================================================

#include "Graph.h"
#include "DenseGraph.h"       // remove if B level
#include "SparseGraph.h"      // remove if B level
#include <iostream>
using namespace std;

int main ( void )
{
   Graph *gp;

   int nv, ne;
   cin >> nv >> ne;
   //gp = new Graph(nv,ne);            // B level
   gp = new SparseGraph(nv,ne);        // A level
   cin >> (*gp);
   //cout << (*gp);

   //----------------------------------------------
   // Part 1: Complete BFS with node 0 as source
   printf("\n\n");
   printf("Part 1: Breadth First Search\n");
   int source = 0;   // source vertex
   gp->BFS(source);
   if ( gp->size() <= 10 )
      gp->printBFSTable(source);   // for debugging purposes, not required
   else
      printf("No BFS Table printed\n");


   //----------------------------------------------
   // Part 2: Print most distant vertices
   printf("\n\n");
   printf("Part 2: Most distant vertices from source v%d are: \n",source);
   gp->printMostDistant(source);

   //----------------------------------------------
   // Part 3: Determine if it is a connected graph
   printf("\n\n");
   printf("Part 3: Connectedness\n");
   if ( gp->isConnected() )
      printf("Graph is connected\n");
   else
      printf("Graph is not connected\n");

   //----------------------------------------------
   // Part 4: Print path from vertex 0 to vertex numV-1
   printf("\n\nPart 4: Path from v0 to v%d\n",gp->size()-1);
   int destination = gp->size()-1;
   gp->printBFSPath(source,destination);
   printf("\n");


   delete gp;
   return 0;
}

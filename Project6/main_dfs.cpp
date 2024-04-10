//================================================================
// Matt Kretchmar
// April 2024
// main_dfs.cpp
// This file assumes the A-level implementation for Project 6
// This file implements algorithms associated with DFS search
//================================================================

#include "Graph.h"
#include "DenseGraph.h"       // for A level
#include "SparseGraph.h"      // for A level
#include <iostream>
using namespace std;

int main ( void )
{
   Graph *gp;

   int nv, ne;
   cin >> nv >> ne;
   //gp = new Graph(nv,ne);         // for B level
   gp = new DenseGraph(nv,ne);      // for A level
   //gp = new SparseGraph(nv,ne);   // other choice for A level
   cin >> (*gp);
   //cout << (*gp);

   // Part 1: Complete BFS with node 0 as source
   printf("\n\n");
   printf("Part 1: Depth First Search\n");
   gp->DFS();
   if ( gp->size() <= 10 )
      gp->printDFSTable();

   //gp->printBFSTable(0);   // for debugging purposes
   //printf("Most distant vertices from source v%d are: \n",0);
   //gp->printMostDistant(0);

   // Part 2: Print parenthesization
   printf("\n\n");
   printf("Part 2: Depth First Parenthesization\n");
   if ( gp->size() <= 10 )
      gp->printDFSParenthesization();
   printf("\n");

   // Part 3: Print path from vertex 0 to vertex numV-1
   printf("\n\nPart 3: classify edges\n");
   gp->classifyDFSEdges();

   // Part 4: Create a topological sort from DFS table
   printf("\n\nPart 4: topological sort\n");
   gp->printTopologicalSort();

   delete gp;
   return 0;
}

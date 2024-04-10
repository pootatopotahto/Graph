//===============================
// Graph.h
// Name: Tomer, Caroline, Daniel
// Date: 3 April 2024
// This file contains declaration of Graph class
//===============================

#include <iostream>
#include <string>

using namespace std;

#ifndef Graph_H
#define Graph_H

class Graph{
protected:
    int V;
    int E;
public:
    Graph		                ( void );   //Default constructor
    Graph		                ( int V, int E); // constructor with 
    Graph                       (const Graph &gp); // copy constructor
    ~Graph		                ( void );   //Destructor
    Graph&   operator=	    ( const Graph &gp );

    virtual bool     isEdge         (int v1, int v2) const { return true;}
    virtual int      getWeight      (int v1, int v2) const {return 0;}
    virtual void    insertEdge      (int v1, int v2, int weight) {}
    // BFS based algorithms
    virtual void BFS ( int source );
    virtual void printBFSTable ( int source );
    virtual void printBFSPath ( int s, int d );
    virtual void printMostDistant ( int s );
    virtual bool isConnected ( void );
// DFS based algorithms
    virtual void DFS ( void );
    virtual void DFS_Visit ( int v, int &clock );
    virtual void printDFSTable ( void );
    virtual void printTopologicalSort ( void );
    virtual void printDFSParenthesization( void );
    virtual void classifyDFSEdges ( void );
    virtual void indexSort ( int a[] )

    friend istream & operator>> ( istream &is, Graph &gp );
    friend ostream & operator<< ( ostream &os, const Graph &gp );


};

#endif

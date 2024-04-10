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

    friend istream & operator>> ( istream &is, Graph &gp );
    friend ostream & operator<< ( ostream &os, const Graph &gp );


};

#endif

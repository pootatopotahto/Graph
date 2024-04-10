//===============================
// DenseGraph.h
// Name: Tomer, Caroline, Daniel
// Date: 3 April 2024
// This file contains declaration of DenseGraph class
//===============================

#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

#ifndef DenseGraph_H
#define DenseGraph_H

class DenseGraph : public Graph{
private: 
    int **matrix;
public:
    DenseGraph		                ( void );   //Default constructor
    DenseGraph		                ( int V, int E); // constructor with item
    DenseGraph                       (const DenseGraph &gp); // copy constructor
    ~DenseGraph		                ( void );   //Destructor
    DenseGraph&   operator=	    ( const DenseGraph &gp );

    bool     isEdge         (int v1, int v2) const;
    int       getWeight   (int v1, int v2)const;
    void    insertEdge      (int v1, int v2, int weight);
    



};

#endif
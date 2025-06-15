#ifndef BELLMAN_H
#define BELLMAN_H

#include <string>
using namespace std;

// Function to implement Bellman-Ford algorithm
void BF(int edgeList[][3], int numEdges, char startVertex, int BFValue[], int BFPrev[]);

// Function to find and return path from start to goal vertex
string BF_Path(int edgeList[][3], int numEdges, char startVertex, char goalVertex);

#endif
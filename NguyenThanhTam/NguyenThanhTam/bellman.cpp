#include "bellman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
using namespace std;

// Function to implement Bellman-Ford algorithm
void BF(int edgeList[][3], int numEdges, char startVertex, int BFValue[], int BFPrev[]) {
    const int INF = numeric_limits<int>::max();
    
    // Initialize distances and previous vertices
    for (int i = 0; i < 50; i++) {
        BFValue[i] = INF;
        BFPrev[i] = -1;
    }
    
    // Set distance to start vertex as 0
    BFValue[(int)startVertex] = 0;
    
    // Get all unique vertices from edge list
    vector<int> vertices;
    for (int i = 0; i < numEdges; i++) {
        bool found0 = false, found1 = false;
        for (size_t j = 0; j < vertices.size(); j++) {
            if (vertices[j] == edgeList[i][0]) found0 = true;
            if (vertices[j] == edgeList[i][1]) found1 = true;
        }
        if (!found0) vertices.push_back(edgeList[i][0]);
        if (!found1) vertices.push_back(edgeList[i][1]);
    }
    
    int numVertices = vertices.size();
    
    // Relax edges repeatedly
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edgeList[j][0];
            int v = edgeList[j][1];
            int weight = edgeList[j][2];
            
            if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
                BFValue[v] = BFValue[u] + weight;
                BFPrev[v] = u;
            }
        }
    }
    
    // Check for negative cycles
    for (int j = 0; j < numEdges; j++) {
        int u = edgeList[j][0];
        int v = edgeList[j][1];
        int weight = edgeList[j][2];
        
        if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
            cout << "Negative cycle detected!" << endl;
            return;
        }
    }
    
    // Print results
    cout << "Bellman-Ford shortest distances from " << char(startVertex) << ":" << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        int vertex = vertices[i];
        if (BFValue[vertex] == INF) {
            cout << "To " << char(vertex) << ": INF" << endl;
        } else {
            cout << "To " << char(vertex) << ": " << BFValue[vertex] << endl;
        }
    }
}

// Function to find and return path from start to goal vertex
string BF_Path(int edgeList[][3], int numEdges, char startVertex, char goalVertex) {
    const int INF = numeric_limits<int>::max();
    int BFValue[50];
    int BFPrev[50];
    
    // Initialize distances and previous vertices
    for (int i = 0; i < 50; i++) {
        BFValue[i] = INF;
        BFPrev[i] = -1;
    }
    
    // Set distance to start vertex as 0
    BFValue[(int)startVertex] = 0;
    
    // Get all unique vertices from edge list
    vector<int> vertices;
    for (int i = 0; i < numEdges; i++) {
        bool found0 = false, found1 = false;
        for (size_t j = 0; j < vertices.size(); j++) {
            if (vertices[j] == edgeList[i][0]) found0 = true;
            if (vertices[j] == edgeList[i][1]) found1 = true;
        }
        if (!found0) vertices.push_back(edgeList[i][0]);
        if (!found1) vertices.push_back(edgeList[i][1]);
    }
    
    int numVertices = vertices.size();
    
    // Relax edges repeatedly
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edgeList[j][0];
            int v = edgeList[j][1];
            int weight = edgeList[j][2];
            
            if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
                BFValue[v] = BFValue[u] + weight;
                BFPrev[v] = u;
            }
        }
    }
    
    // Check if goal is reachable
    if (BFValue[(int)goalVertex] == INF) {
        return "No path exists";
    }
    
    // Handle case where start and goal are the same
    if (startVertex == goalVertex) {
        string result = "";
        result += char(startVertex);
        return result;
    }
    
    // Reconstruct path
    vector<char> path;
    int current = (int)goalVertex;
    
    while (current != -1) {
        path.push_back(char(current));
        current = BFPrev[current];
    }
    
    // Reverse to get path from start to goal
    reverse(path.begin(), path.end());
    
    // Convert to string with spaces
    stringstream ss;
    for (size_t i = 0; i < path.size(); i++) {
        ss << path[i];
        if (i < path.size() - 1) {
            ss << " ";
        }
    }
    string result = ss.str();
    
    cout << "Shortest path from " << char(startVertex) << " to " << char(goalVertex) << ": " << result << endl;
    cout << "Total distance: " << BFValue[(int)goalVertex] << endl;
    
    return result;
}
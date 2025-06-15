#include "bellman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Function to implement Bellman-Ford algorithm
void BF(int edgeList[][3], int numEdges, char startVertex, int BFValue[], int BFPrev[]) {
    // Initialize distances and previous vertices
    for (int i = 0; i < 50; i++) {
        BFValue[i] = INT_MAX;
        BFPrev[i] = -1;
    }

    // Set distance to start vertex as 0
    BFValue[(int)startVertex] = 0; // Cast char to int

    // Get all unique vertices from edge list
    vector<int> vertices;
    for (int i = 0; i < numEdges; i++) {
        if (find(vertices.begin(), vertices.end(), edgeList[i][0]) == vertices.end()) {
            vertices.push_back(edgeList[i][0]);
        }
        if (find(vertices.begin(), vertices.end(), edgeList[i][1]) == vertices.end()) {
            vertices.push_back(edgeList[i][1]);
        }
    }

    int numVertices = vertices.size();

    // Relax edges repeatedly
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edgeList[j][0];
            int v = edgeList[j][1];
            int weight = edgeList[j][2];

            if (BFValue[u] != INT_MAX && BFValue[u] + weight < BFValue[v]) {
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

        if (BFValue[u] != INT_MAX && BFValue[u] + weight < BFValue[v]) {
            cout << "Negative cycle detected!" << endl;
            return;
        }
    }

    // Print results
    cout << "Bellman-Ford shortest distances from " << char(startVertex) << ":" << endl;
    for (int vertex : vertices) {
        if (BFValue[vertex] == INT_MAX) {
            cout << "To " << char(vertex) << ": INF" << endl;
        } else {
            cout << "To " << char(vertex) << ": " << BFValue[vertex] << endl;
        }
    }
}

// Function to find and return path from start to goal vertex
string BF_Path(int edgeList[][3], int numEdges, char startVertex, char goalVertex) {
    int BFValue[50];
    int BFPrev[50];

    // Initialize distances and previous vertices
    for (int i = 0; i < 50; i++) {
        BFValue[i] = INT_MAX;
        BFPrev[i] = -1;
    }

    // Set distance to start vertex as 0
    BFValue[(int)startVertex] = 0; // Cast char to int

    // Get all unique vertices from edge list
    vector<int> vertices;
    for (int i = 0; i < numEdges; i++) {
        if (find(vertices.begin(), vertices.end(), edgeList[i][0]) == vertices.end()) {
            vertices.push_back(edgeList[i][0]);
        }
        if (find(vertices.begin(), vertices.end(), edgeList[i][1]) == vertices.end()) {
            vertices.push_back(edgeList[i][1]);
        }
    }

    int numVertices = vertices.size();

    // Relax edges repeatedly
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edgeList[j][0];
            int v = edgeList[j][1];
            int weight = edgeList[j][2];

            if (BFValue[u] != INT_MAX && BFValue[u] + weight < BFValue[v]) {
                BFValue[v] = BFValue[u] + weight;
                BFPrev[v] = u;
            }
        }
    }

    // Check if goal is reachable
    if (BFValue[(int)goalVertex] == INT_MAX) { // Cast char to int
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
    int current = (int)goalVertex; // Cast char to int

    while (current != -1) {
        path.push_back(char(current));
        current = BFPrev[current];
    }

    // Reverse to get path from start to goal
    reverse(path.begin(), path.end());

    // Convert to string with spaces
    string result = "";
    for (size_t i = 0; i < path.size(); i++) { // Use size_t to avoid signed/unsigned comparison
        result += path[i];
        if (i < path.size() - 1) {
            result += " ";
        }
    }

    cout << "Shortest path from " << char(startVertex) << " to " << char(goalVertex) << ": " << result << endl;
    cout << "Total distance: " << BFValue[(int)goalVertex] << endl; // Cast char to int

    return result;
}

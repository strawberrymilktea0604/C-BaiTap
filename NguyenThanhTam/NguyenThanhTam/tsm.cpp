#include "tsm.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Function to solve Traveling Salesman Problem using brute force
void Traveling(int edgeList[][3], int numEdges, char startVertex) {
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

    // Create adjacency matrix
    int adjMatrix[128][128];
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            adjMatrix[i][j] = INT_MAX;
        }
    }

    // Fill adjacency matrix with edge weights
    for (int i = 0; i < numEdges; i++) {
        int u = edgeList[i][0];
        int v = edgeList[i][1];
        int weight = edgeList[i][2];
        adjMatrix[u][v] = min(adjMatrix[u][v], weight);
        adjMatrix[v][u] = min(adjMatrix[v][u], weight); // Assuming undirected graph
    }

    // Remove start vertex from vertices list for permutation
    vector<int> otherVertices;
    for (int vertex : vertices) {
        if (vertex != (int)startVertex) { // Cast char to int
            otherVertices.push_back(vertex);
        }
    }

    int minCost = INT_MAX;
    vector<int> bestPath;

    // Try all possible permutations
    sort(otherVertices.begin(), otherVertices.end());

    do {
        int currentCost = 0;
        int currentVertex = (int)startVertex; // Cast char to int
        vector<int> currentPath;
        currentPath.push_back((int)startVertex); // Cast char to int

        bool validPath = true;

        // Calculate cost of current permutation
        for (int nextVertex : otherVertices) {
            if (adjMatrix[currentVertex][nextVertex] == INT_MAX) {
                validPath = false;
                break;
            }
            currentCost += adjMatrix[currentVertex][nextVertex];
            currentPath.push_back(nextVertex);
            currentVertex = nextVertex;
        }

        // Return to start vertex
        if (validPath && adjMatrix[currentVertex][(int)startVertex] != INT_MAX) { // Cast char to int
            currentCost += adjMatrix[currentVertex][(int)startVertex]; // Cast char to int
            currentPath.push_back((int)startVertex); // Cast char to int

            if (currentCost < minCost) {
                minCost = currentCost;
                bestPath = currentPath;
            }
        }

    } while (next_permutation(otherVertices.begin(), otherVertices.end()));

    if (minCost == INT_MAX) {
        cout << "No valid TSP tour found!" << endl;
        return;
    }

    // Print the shortest path
    cout << "Shortest TSP tour starting from " << char(startVertex) << ":" << endl;
    for (size_t i = 0; i < bestPath.size(); i++) { // Use size_t to avoid signed/unsigned comparison
        cout << char(bestPath[i]);
        if (i < bestPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total cost: " << minCost << endl;
}

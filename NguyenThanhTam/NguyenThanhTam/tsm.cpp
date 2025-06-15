#include "tsm.h"

// Function to solve Traveling Salesman Problem using brute force
void Traveling(int edgeList[][3], int numEdges, char startVertex) {
    const int INF = 1000000000;

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

    if (vertices.size() < 2) {
        cout << "Not enough vertices for TSP!" << endl;
        return;
    }

    // Create adjacency matrix
    int adjMatrix[256][256];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            adjMatrix[i][j] = INF;
        }
    }

    // Fill adjacency matrix with edge weights
    for (int i = 0; i < numEdges; i++) {
        int u = edgeList[i][0];
        int v = edgeList[i][1];
        int weight = edgeList[i][2];

        if (u >= 0 && u < 256 && v >= 0 && v < 256) {
            if (adjMatrix[u][v] > weight) adjMatrix[u][v] = weight;
            if (adjMatrix[v][u] > weight) adjMatrix[v][u] = weight;
        }
    }

    // Remove start vertex from vertices list for permutation
    vector<int> otherVertices;
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i] != (int)startVertex) {
            otherVertices.push_back(vertices[i]);
        }
    }

    if (otherVertices.empty()) {
        cout << "Only one vertex in the graph!" << endl;
        return;
    }

    int minCost = INF;
    vector<int> bestPath;

    // Try all possible permutations
    sort(otherVertices.begin(), otherVertices.end());

    do {
        int currentCost = 0;
        int currentVertex = (int)startVertex;
        vector<int> currentPath;
        currentPath.push_back((int)startVertex);

        bool validPath = true;

        // Calculate cost of current permutation
        for (size_t i = 0; i < otherVertices.size(); i++) {
            int nextVertex = otherVertices[i];
            if (currentVertex < 0 || currentVertex >= 256 || nextVertex < 0 || nextVertex >= 256 ||
                adjMatrix[currentVertex][nextVertex] == INF) {
                validPath = false;
                break;
            }
            currentCost += adjMatrix[currentVertex][nextVertex];
            currentPath.push_back(nextVertex);
            currentVertex = nextVertex;
        }

        // Return to start vertex
        if (validPath && currentVertex >= 0 && currentVertex < 256 &&
            (int)startVertex >= 0 && (int)startVertex < 256 &&
            adjMatrix[currentVertex][(int)startVertex] != INF) {
            currentCost += adjMatrix[currentVertex][(int)startVertex];
            currentPath.push_back((int)startVertex);

            if (currentCost < minCost) {
                minCost = currentCost;
                bestPath = currentPath;
            }
        }

    } while (next_permutation(otherVertices.begin(), otherVertices.end()));

    if (minCost == INF || bestPath.empty()) {
        cout << "No valid TSP tour found!" << endl;
        return;
    }

    // Print the shortest path
    cout << "Shortest TSP tour starting from " << char(startVertex) << ":" << endl;
    for (size_t i = 0; i < bestPath.size(); i++) {
        cout << char(bestPath[i]);
        if (i < bestPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total cost: " << minCost << endl;
}

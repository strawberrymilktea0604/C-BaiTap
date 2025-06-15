#include "bellman.h"

// Function to implement Bellman-Ford algorithm
void BF(int edgeList[][3], int numEdges, char startVertex, int BFValue[], int BFPrev[]) {
    const int INF = 1000000000;

    // Get all unique vertices from edge list first
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

    int numVertices = (int)vertices.size();

    // Initialize distances - only for vertices that exist in the graph
    for (size_t i = 0; i < vertices.size(); i++) {
        int vertex = vertices[i];
        if (vertex >= 0 && vertex < 256) {
            BFValue[vertex] = INF;
            BFPrev[vertex] = -1;
        }
    }

    // Set distance to start vertex as 0
    if ((int)startVertex >= 0 && (int)startVertex < 256) {
        BFValue[(int)startVertex] = 0;
    }

    // Relax edges repeatedly
    bool updated = true;
    for (int iteration = 0; iteration < numVertices - 1 && updated; iteration++) {
        updated = false;
        for (int i = 0; i < numEdges; i++) {
            int u = edgeList[i][0];
            int v = edgeList[i][1];
            int weight = edgeList[i][2];

            if (u >= 0 && u < 256 && v >= 0 && v < 256) {
                if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
                    BFValue[v] = BFValue[u] + weight;
                    BFPrev[v] = u;
                    updated = true;
                }
            }
        }
    }

    // Check for negative cycles
    bool hasNegativeCycle = false;
    for (int i = 0; i < numEdges; i++) {
        int u = edgeList[i][0];
        int v = edgeList[i][1];
        int weight = edgeList[i][2];

        if (u >= 0 && u < 256 && v >= 0 && v < 256) {
            if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
    }

    if (hasNegativeCycle) {
        cout << "Negative cycle detected!" << endl;
        return;
    }

    // Print results
    cout << "Bellman-Ford shortest distances from " << char(startVertex) << ":" << endl;
    for (size_t i = 0; i < vertices.size(); i++) {
        int vertex = vertices[i];
        if (vertex >= 0 && vertex < 256) {
            if (BFValue[vertex] == INF) {
                cout << "To " << char(vertex) << ": INF" << endl;
            } else {
                cout << "To " << char(vertex) << ": " << BFValue[vertex] << endl;
            }
        }
    }
}

// Function to find and return path from start to goal vertex
string BF_Path(int edgeList[][3], int numEdges, char startVertex, char goalVertex) {
    const int INF = 1000000000;
    int BFValue[256];
    int BFPrev[256];

    // Get all unique vertices from edge list first
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

    int numVertices = (int)vertices.size();

    // Initialize distances
    for (int i = 0; i < 256; i++) {
        BFValue[i] = INF;
        BFPrev[i] = -1;
    }

    // Set distance to start vertex as 0
    if ((int)startVertex >= 0 && (int)startVertex < 256) {
        BFValue[(int)startVertex] = 0;
    }

    // Relax edges repeatedly
    for (int iteration = 0; iteration < numVertices - 1; iteration++) {
        for (int i = 0; i < numEdges; i++) {
            int u = edgeList[i][0];
            int v = edgeList[i][1];
            int weight = edgeList[i][2];

            if (u >= 0 && u < 256 && v >= 0 && v < 256) {
                if (BFValue[u] != INF && BFValue[u] + weight < BFValue[v]) {
                    BFValue[v] = BFValue[u] + weight;
                    BFPrev[v] = u;
                }
            }
        }
    }

    // Check if goal is reachable
    if ((int)goalVertex < 0 || (int)goalVertex >= 256 || BFValue[(int)goalVertex] == INF) {
        cout << "No path exists from " << char(startVertex) << " to " << char(goalVertex) << endl;
        return "No path exists";
    }

    // Handle case where start and goal are the same
    if (startVertex == goalVertex) {
        string result = "";
        result += char(startVertex);
        cout << "Path from " << char(startVertex) << " to " << char(goalVertex) << ": " << result << endl;
        cout << "Total distance: 0" << endl;
        return result;
    }

    // Reconstruct path
    vector<char> path;
    int current = (int)goalVertex;

    while (current != -1 && current >= 0 && current < 256) {
        path.push_back(char(current));
        current = BFPrev[current];
    }

    // Check if we successfully traced back to start
    if (path.empty() || path[path.size()-1] != startVertex) {
        cout << "No valid path found from " << char(startVertex) << " to " << char(goalVertex) << endl;
        return "No path exists";
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

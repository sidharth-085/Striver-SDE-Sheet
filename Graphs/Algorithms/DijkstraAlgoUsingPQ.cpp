#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

vector<int> dijkstraAlgorithm(vector<vector<int>> &Edges, int n, int e, int source) {
    vector<int> weights(n, INT_MAX); // Initialize all weights to infinity except the source
    weights[source] = 0;

    vector<vector<pair<int, int>>> edges(n); // Create an adjacency list to store the edges

    // Populate the adjacency list with the given edges and their weights
    for (int i=0; i<e; i++) {
        int first = Edges[i][0];
        int second = Edges[i][1];
        int weight = Edges[i][2];

        edges[first].push_back({weight, second});
        edges[second].push_back({weight, first});
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, source}); // Push the source vertex with weight 0 into the priority queue

    // Run Dijkstra's algorithm
    while (!pq.empty()) {
        pair<int, int> top = pq.top(); // Get the vertex with the minimum weight
        pq.pop();

        int topWeight = top.first; // Current weight of the top vertex
        int topVertex = top.second; // Index of the top vertex

        // Iterate through all neighboring vertices of the top vertex
        for (int i=0; i < edges[topVertex].size(); i++) {
            pair<int, int> neighbour = edges[topVertex][i]; // Get the neighboring vertex and its weight
            int edgeWeight = neighbour.first; // Weight of the neighboring vertex
            int edgeVertex = neighbour.second; // Index of the neighboring vertex

            // Update the weight of the neighboring vertex if a shorter path is found
            if (topWeight + edgeWeight < weights[edgeVertex]) {
                weights[edgeVertex] = topWeight + edgeWeight;
                pq.push({topWeight + edgeWeight, edgeVertex});
            }
        }
    }
    return weights; // Return the shortest path weights from the source vertex to all other vertices
}
#include <vector>
#include <climits>
#include <queue>
using namespace std;

vector<pair<pair<int,int>,int>> calculatePrimsMST(int n, int e, vector<pair<pair<int,int>,int>> &graph) {
    vector<vector<pair<int, int>>> edges(n+1); // Adjacency list to store graph edges

    for (int i=0; i<e; i++) {
        int first = graph[i].first.first;
        int second = graph[i].first.second;
        int weight = graph[i].second;

        edges[first].push_back({weight, second}); // Add edge to adjacency list
        edges[second].push_back({weight, first}); // Assuming an undirected graph
    }

    vector<int> weights(n+1, INT_MAX); // Array to store weights for each vertex
    weights[1] = 0; // Weight of starting vertex is 0

    vector<int> parent(n+1); // Array to store parent of each vertex in the MST
    parent[1] = -1; // Starting vertex has no parent

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 1}); // Starting vertex with weight 0

    vector<bool> visited(n+1, false); // Array to track visited vertices

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int topVertex = top.second;
        int topWeight = top.first;

        visited[topVertex] = true; // Mark the vertex as visited

        for (int i=0; i<edges[topVertex].size(); i++) {
            pair<int, int> neighbour = edges[topVertex][i];
            int edgeWeight = neighbour.first;
            int edgeVertex = neighbour.second;

            if (weights[edgeVertex] > edgeWeight && !visited[edgeVertex]) {
                weights[edgeVertex] = edgeWeight; // Update the weight of the vertex

                parent[edgeVertex] = topVertex; // Set the parent of the vertex
                pq.push({edgeWeight, edgeVertex}); // Push the vertex into the priority queue for further exploration
            }
        }
    }

    vector<pair<pair<int,int>,int>> ans; // Vector to store the MST edges

    for (int i=2; i<=n; i++) {
        int first = min(i, parent[i]);
        int second = max(i, parent[i]);
        int weight = weights[i];

        ans.push_back({{first, second}, weight}); // Add the edge to the MST
    }
    return ans;
}
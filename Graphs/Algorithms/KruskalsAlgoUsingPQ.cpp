#include <vector>
#include <queue>
using namespace std;

class Edge {
public:
    int source;
    int destination;
    int weight;
};

class Compare {
public:
    bool operator()(const Edge &e1, const Edge &e2) {
        return e1.weight > e2.weight;
    }
};

// Find function for the disjoint set
int find(int vertex, vector<int>& parent) { // iterative code
    int current = vertex;
    while (current != parent[current]) {
        current = parent[current];
    }
    return current;
}

int find(int vertex, vector<int> &parent) { // recursive code
    if (vertex == parent[vertex]) {
        return vertex;
    }
    return find(parent[vertex], parent);
}

int kruskalMST(int n, int e, vector<vector<int>>& graph) {
    // Create a vector to store the edges
    vector<Edge> edges(e);

    vector<int> ans;

    // Store the graph edges in the Edge class format
    for (int i = 0; i < e; i++) {
        edges[i].source = graph[i][0];
        edges[i].destination = graph[i][1];
        edges[i].weight = graph[i][2];
    }

    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int count = 0, sum = 0;

    // Create a priority queue (min-heap) to store the edges sorted by weight
    priority_queue<Edge, vector<Edge>, Compare> pq;
    
    // Push all the edges into the priority queue
    for (auto e: edges) {
        pq.push(e);
    }

    while (count != n - 1) {
        Edge top = pq.top();
        pq.pop();

        // Extract the minimum weight, source, and destination from the top edge
        int minRow = top.source;
        int minCol = top.destination;
        int minWeight = top.weight;

        // Find the parents of the source and destination vertices
        int parent1 = find(minRow, parent);
        int parent2 = find(minCol, parent);

        if (parent1 != parent2) {
            // If the source and destination vertices belong to different sets,
            // add the current edge to the MST and merge the sets
            count++;
            sum = sum + minWeight;
            parent[parent1] = parent[parent2];
        }
    }

    return sum;
}

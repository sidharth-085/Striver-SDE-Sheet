#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Depth-first search for topological sort
void dfsForTopologicalSort(vector<vector<int>> &graph, int startVertex, vector<bool> &visited, stack<int> &s) {
    visited[startVertex] = true;

    // Traverse neighbors of the current vertex
    for (int neighbour : graph[startVertex]) {
        if (!visited[neighbour]) {
            // Recursive call for unvisited neighbors
            dfsForTopologicalSort(graph, neighbour, visited, s);
        }
    }

    // Push the current vertex to the stack
    s.push(startVertex);
}

// Function for topological sort
vector<int> topologicalSort(vector<vector<int>> &edges, int n, int e)  {
    vector<vector<int>> graph(n); // adjacency list

    // Build the graph using the given edges
    for (int i = 0; i < e; i++) {
        int first = edges[i][0];
        int second = edges[i][1];

        graph[first].push_back(second);
    }

    vector<bool> visited(n, false);
    stack<int> s;

    // Perform DFS on all unvisited vertices
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsForTopologicalSort(graph, i, visited, s);
        }
    }

    vector<int> ans;
    // Pop elements from the stack and add them to the result
    while (!s.empty()) {
        int top = s.top();
        s.pop();

        ans.push_back(top);
    }
    return ans;
}
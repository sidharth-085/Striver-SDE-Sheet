#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Bipartite graph is a graph in which we color the graph such that no two adjacent vertices 
// have the same color.

// Approach 1: DFS METHOD

bool DFS(vector<vector<int>> &graph, int startVertex, vector<char> &color) {
    // If the color of the current vertex is not assigned, assign it 'G' (Green).
    if (color[startVertex] == '\0') {
        color[startVertex] = 'G';
    }

    for (int i = 0; i < graph[startVertex].size(); i++) {
        int neighbour = graph[startVertex][i];
        
        // If the neighbor has the same color as the current vertex, the graph is not bipartite.
        if (color[neighbour] == color[startVertex]) {
            return false;
        }

        // If the neighbor's color is not assigned, assign it the opposite color of the current vertex.
        if (color[neighbour] == '\0') {
            if (color[startVertex] == 'G') {
                color[neighbour] = 'Y'; // 'Y' represents Yellow.
            } else {
                color[neighbour] = 'G';
            }

            // Recursively call DFS on the neighbor.
            bool ans = DFS(graph, neighbour, color);
            if (!ans) {
                return false;
            }
        }
    }
    return true;
}

bool isGraphBipartite(vector<vector<int>> &edges) {
    // First, create an adjacency list from the adjacency matrix.
    int n = edges.size();
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (edges[i][j] == 1) {
                // Add edges to the adjacency list.
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    vector<char> color(n, '\0'); // We are using a color vector instead of a visited vector.

    for (int i = 0; i < n; i++) {
        if (color[i] == '\0') {
            // If the color of the current vertex is not assigned, call DFS on it.
            bool ans = DFS(graph, i, color);
            if (!ans) {
                return false;
            }
        }
    }
    return true;
}

// Approach 2: BFS METHOD

bool BFS(vector<vector<int>> &graph, int startVertex, vector<char> &color) {
    queue<int> q;
    q.push(startVertex);

    color[startVertex] = 'G';

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        for (int neighbour : graph[vertex]) {
            // If the neighbor has the same color as the current vertex, the graph is not bipartite.
            if (color[neighbour] == color[vertex]) {
                return false;
            }

            // If the neighbor's color is not assigned, assign it the opposite color of the current vertex.
            if (color[neighbour] == '\0') {
                if (color[vertex] == 'G') {
                    color[neighbour] = 'Y'; // 'Y' represents Yellow.
                } 
                else {
                    color[neighbour] = 'G';
                }
                q.push(neighbour);
            }
        }
    }
    return true;
}

bool isGraphBipartite(vector<vector<int>> &edges) {
    // First, create an adjacency list from the adjacency matrix.
    int n = edges.size();
    vector<vector<int>> graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (edges[i][j] == 1) {
                // Add edges to the adjacency list.
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    vector<char> color(n, '\0'); // We are using a color vector instead of a visited vector.

    for (int i = 0; i < n; i++) {
        if (color[i] == '\0') {
            // If the color of the current vertex is not assigned, call BFS on it.
            bool ans = BFS(graph, i, color);
            if (!ans) {
                return false;
            }
        }
    }
    return true;
}

#include <vector>
#include <string>
using namespace std;

// Approach 1: Using Adjacency Matrix (DFS)

bool solve(vector<vector<int>> &edges, int n, vector<bool> &visited, int startVertex, int parent) {
    visited[startVertex] = true;

    for (int i=1; i<=n; i++) {
        if (i == startVertex) {
            continue;
        }
        if (edges[startVertex][i] == 1) {
            if (!visited[i]) {
                bool ans = solve(edges, n, visited, i, startVertex);
                if (ans) {
                    return true;
                }
            }
            else if (i != parent) {
                return true;
            }
        }
    }

    return false;
}

bool cycleDetectionHelper(vector<vector<int>> &edges, int n) {
    vector<bool> visited(n+1, false);

    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            bool ans = solve(edges, n, visited, i, -1);
            if (ans) {
                return true;
            }
        }
    }
    return false;
}

string cycleDetection(vector<vector<int>>& Edges, int n, int e) {
    vector<vector<int>> edges(n+1, vector<int>(n+1, 0));

    for (int i=0; i<e; i++) {
        int first = Edges[i][0];
        int second = Edges[i][1];

        edges[first][second] = 1;
        edges[second][first] = 1;
    }

    bool isCyclic = cycleDetectionHelper(edges, n);

    return isCyclic ? "Yes" : "No";
}

// Approach 2: Using Adjacency List (DFS)

bool solve(vector<vector<int>> &edges, int n, vector<bool> &visited, int startVertex, int parent) {
    visited[startVertex] = true;

    for (int i=0; i<edges[startVertex].size(); i++) {
        int neighbour = edges[startVertex][i];
        if (!visited[neighbour]) {
            bool ans = solve(edges, n, visited, neighbour, startVertex);
            if (ans) {
                return true;
            }
        }
        else if (neighbour != parent) {
            return true;
        }
    }

    return false;
}

bool cycleDetectionHelper(vector<vector<int>> &edges, int n) {
    vector<bool> visited(n+1, false);

    for (int i=1; i<=n; i++) {
        if (!visited[i]) {
            bool ans = solve(edges, n, visited, i, -1);
            if (ans) {
                return true;
            }
        }
    }
    return false;
}

string cycleDetection (vector<vector<int>>& Edges, int n, int e) {
    vector<vector<int>> edges(n+1);

    for (int i=0; i<e; i++) {
        int first = Edges[i][0];
        int second = Edges[i][1];

        edges[first].push_back(second);
        edges[second].push_back(first);
    }

    bool isCyclic = cycleDetectionHelper(edges, n);

    return isCyclic ? "Yes" : "No";
}
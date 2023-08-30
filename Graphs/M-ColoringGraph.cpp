#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Brute Force Recursive Approach (Explores all possible answers)

// Function to check if the current coloring is correct
bool isCorrect(vector<vector<int>> &graph, vector<int> &color, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Check if there is an edge between vertices i and j
            // If there is an edge and they have the same color, return false
            if (graph[i][j] == 1 && color[i] == color[j]) {
                return false;
            }
        }
    }
    // If no conflicts are found, return true
    return true;
}

// Recursive helper function for graph coloring
bool graphColoringHelper(vector<vector<int>> &graph, int startVertex, int n, int m, vector<int> &color) {
    // If we have colored all the vertices, check if the coloring is correct
    if (startVertex == n) {
        if (isCorrect(graph, color, n)) {
            return true;
        }
        return false;
    }

    // Try different colors for the current vertex
    for (int i = 1; i <= m; i++) {
        color[startVertex] = i; // Assign color i to the current vertex

        // Recursively color the remaining vertices
        bool ans = graphColoringHelper(graph, startVertex + 1, n, m, color);
        if (ans) {
            return true; // If a valid coloring is found, return true
        }

        // Backtrack by unassigning the color for the current vertex
        color[startVertex] = 0;
    }
    // If no valid coloring is found, return false
    return false;
}

// Function to perform graph coloring
string graphColoring(vector<vector<int>> &graph, int m) {
    int n = graph.size();
    vector<int> color(n, 0); // Initialize color array with 0 (no color assigned)

    // Start the graph coloring process from the first vertex
    bool ans = graphColoringHelper(graph, 0, n, m, color);

    if (ans == true) {
        return "YES"; // If a valid coloring is found, return "YES"
    }
    return "NO"; // If no valid coloring is found, return "NO"
}

// Backtracking Approach (Little Optimized than Recursion)

// Function to check if it is safe to assign a newColor to the startVertex
bool isSafe(vector<vector<int>> &graph, int startVertex, int n, int m, vector<int> &color, int newColor) {
    for (int i = 0; i < n; i++) {
        // Check if there is an edge between startVertex and vertex i
        // If there is an edge and vertex i has the same color as newColor, return false
        if (graph[startVertex][i] == 1 && i != startVertex && color[i] == newColor) {
            return false;
        }
    }
    // If no conflicts are found, return true
    return true;
}

// Recursive helper function for graph coloring using backtracking
bool graphColoringHelper(vector<vector<int>> &graph, int startVertex, int n, int m, vector<int> &color) {
    // If we have colored all the vertices, return true
    if (startVertex == n) {
        return true;
    }

    // Try different colors for the current vertex
    for (int i = 1; i <= m; i++) {
        if (isSafe(graph, startVertex, n, m, color, i)) {
            color[startVertex] = i; // Assign color i to the current vertex

            // Recursively color the remaining vertices
            bool ans = graphColoringHelper(graph, startVertex + 1, n, m, color);
            if (ans) {
                return true; // If a valid coloring is found, return true
            }

            // Backtrack by unassigning the color for the current vertex
            color[startVertex] = 0;
        }
    }
    // If no valid coloring is found, return false
    return false;
}

// Function to perform graph coloring using backtracking
string graphColoring(vector<vector<int>> &graph, int m) {
    int n = graph.size();
    vector<int> color(n, 0); // Initialize color array with 0 (no color assigned)

    // Start the graph coloring process from the first vertex
    bool ans = graphColoringHelper(graph, 0, n, m, color);

    if (ans == true) {
        return "YES"; // If a valid coloring is found, return "YES"
    }
    return "NO"; // If no valid coloring is found, return "NO"
}
#include <iostream>
#include <vector>
using namespace std;

// Flyod Warshall Algorithm is little different algorithm to find the shortest path. 
// This algorithm is multi-source shortest path algorithm. 

// This algorithm finds shortest path between every two vertex using 2-D matrix.

// This algorithm also involves DP in it because we are doing the pre-computation for
// every vertex by considering that every path between two vertex should pass via 
// specific vertex.

// We can use it for directed graphs as well as for undirected graphs just make two 
// directed edges. It also works for negative edges. If all the edges are positive,
// then we can apply dijkstra algorithm for every vertex as source and get the shortest
// path for every vertex to every vertex as 2-D matrix.

// Time Complexity (if dijsktra use): O(N * M * Log N) 
// where N are number of vertex and M number of edges

// Time Complexity: O(N^3)
// Space Complexity: O(N^2)

vector<vector<int>> floydWarshall(int n, int m, vector<vector<int>> &edges) {
    // step 1: first create the graph from given edges 
    const int mod = 1e9;

    vector<vector<int>> graph(n+1, vector<int>(n+1, mod));

    for (int i=1; i<=n; i++) {
        graph[i][i] = 0;
    }

    for (int i=0; i<m; i++) {
        int first = edges[i][0];
        int second = edges[i][1];
        int weight = edges[i][2];

        graph[first][second] = weight;
    }

    // step 2: after creating of graph, now start the flyod warshall algorithm
    // we will do the work for every vertex, we find the distance from i to j passing
    // through "via" because we want to find shortest distance for every vertex to 
    // every vertex in the form of grid.

    for (int via = 1; via <= n; via++) { 
        // loop for current grid passes through a specific vertex

        // now just, traverse the complete grid and edit it
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                // if weight from i to via or via to j is mod means there is shortest
                // distance from i to via or via to j is mod so dont consider it. 

                if (graph[i][via] == mod || graph[via][j] == mod) {
                    continue;
                }

                // when the distance through "via" is less than the current i to j
                // distance, update the shortest distance for i to j.

                if (graph[i][via] + graph[via][j] < graph[i][j]) {
                    graph[i][j] = graph[i][via] + graph[via][j];
                }
            } 
        }
    }

    // Here, if there is negative cycle, we know that for negative cycle, every
    // vertex tries to minimize the result due to negative weights and also for 
    // node to node path becomes negative which ideally should be 0.

    for (int i=1; i<=n; i++) {
        if (graph[i][i] < 0) { // if negative cycle found return {{-1}}.
            return {{-1}};
        }
    }
    
    return graph; // finally return the graph
}

int floydWarshall(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    vector<vector<int>> shortestPath = floydWarshall(n, m, edges);

    return shortestPath[src][dest];
    // return the answer for given source and destination, here we have shortest distance
    // from every vertex to every vertex.
}
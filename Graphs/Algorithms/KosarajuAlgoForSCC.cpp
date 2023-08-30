#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Kosaraju's Algorithm is useful for finding the Strongly Connected Components easily.
// This Algorithm involves Topological Sorting also.

// Time Complexity : O(N+E) -> Due to DFS Algo
// N is number of vertices
// N is number of Edges

void topologicalSort(vector<vector<int>> &adjList, int startVertex, vector<bool> &visited, stack<int> &stk) {
    // this algorithm works as same as dfs
    visited[startVertex] = true;
    for (int i=0; i<adjList[startVertex].size(); i++) {
        int vertex = adjList[startVertex][i];
        
        if (!visited[vertex] && vertex != startVertex) {
            topologicalSort(adjList, vertex, visited, stk);
        }
    }
    stk.push(startVertex); //  add the startVertex after completing dfs traversal.
}

void dfs(vector<vector<int>> &adjList, int startVertex, vector<bool> &visited, vector<int> &currComponent) {
    visited[startVertex] = true;
    currComponent.push_back(startVertex);

    for (int i=0; i<adjList[startVertex].size(); i++) {
        int vertex = adjList[startVertex][i];

        if (!visited[vertex] && vertex != startVertex) {
            dfs(adjList, vertex, visited, currComponent);
        }
    }
}

vector<vector<int>> stronglyConnectedComponents(int n, vector<vector<int>> &edges) {
    // first we have to make adj list from given above edges matrix
    vector<vector<int>> adjList(n);
    for (int i=0; i<edges.size(); i++) {
        int first = edges[i][0];
        int second = edges[i][1];

        adjList[first].push_back(second);
    }

    // step 1: Traverse the complete graph and do topological sorting
    vector<bool> visited(n, false);
    stack<int> stk;

    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            topologicalSort(adjList, i, visited, stk);
        }
    }

    // step 2: We got the stack of elements in which we have to work
    // now, we have to reverse/transpose the graph

    vector<vector<int>> transAdjList(n);
    for (int i=0; i<n; i++) {
        visited[i] = false; // reset the visited array
        for (int j=0; j<adjList[i].size(); j++) {
            int vertex = adjList[i][j];
            transAdjList[vertex].push_back(i);
        }
    }

    // step 3: Now finally we start the traversal of the strongely connected components
    // from popping every element from stack & do dfs traversal on it.

    int count = 0; // this maintains count of Strongly connected components
    vector<vector<int>> scc;
    while (!stk.empty()) {
        vector<int> currComponent;
        int top = stk.top();
        stk.pop();

        if (!visited[top]) {
            dfs(transAdjList, top, visited, currComponent);
            scc.push_back(currComponent);
            count++;
        }
    }
    return scc;
    // return count;
    // we can return count also for just number of scc.
}
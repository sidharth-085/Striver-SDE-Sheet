#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Kahn's Algorithm is nothing but BFS method of TOPOLOGICAL SORTING
// Time Complexity: O(N+E)

vector<int> kahnAlgorithm(vector<vector<int>> &edges, int n) {
    // we are assuming the vertex are from 1 to n.

    // first create adjacency list from given data
    vector<vector<int>> adjList(n+1);
    vector<int> inDegree(n+1, 0);

    for (int i=0; i<edges.size(); i++) { // create adjList
        int first = edges[i][0];
        int second = edges[i][1];

        adjList[first].push_back(second);
        inDegree[second]++;
    }

    queue<int> q; // make queue for BFS

    for (int i=1; i<=n; i++) {
        if (inDegree[i] == 0) { // first push the vertex having 0 inDegree in queue
            q.push(i);
        }
    }

    vector<int> ans;

    while (!q.empty()) {
        int top = q.front();
        q.pop();
        
        ans.push_back(top); // push the vertex in the ans vector if it does not have any indegree.

        for (int neighbour : adjList[top]) {
            inDegree[neighbour]--; // break the edge between neighbour & top
            if (inDegree[neighbour] == 0) { // if it has zero indegree push in queue
                q.push(neighbour);
            }
        }
    }
    return ans; // finally return the answer
}
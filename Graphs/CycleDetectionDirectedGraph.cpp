#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// Approach 1: DFS Approach

bool dfs(vector<vector<int>> &edges, int n, unordered_map<int, int> &visited, int startVertex) {
    visited[startVertex] = 1;

    for (int i=0; i<edges[startVertex].size(); i++) {
        int neighbour = edges[startVertex][i];
        if (visited[neighbour] == 0) {
            bool ans = dfs(edges, n, visited, neighbour);
            if (ans) {
                return true;
            }
        }
        else if (visited[neighbour] == 1) {
            return true;
        }
    }
    visited[startVertex] = -1; 
    // mark the startVertex as visited by putting -1 value so that it dont get visit again.
    return false;
}

bool solve(vector<vector<int>> &edges, int n) {
    unordered_map<int, int> visited;

    for (int i=1; i <= n; i++) {
        if (visited[i] == 0) {
            bool ans = dfs(edges, n, visited, i);
            if (ans) {
                return true;
            }
        }
    }
    return false;
}

int detectCycleInDirectedGraph(int n, vector<pair<int,int>> &Edges) {
    vector<vector<int>> edges(n+1);
    for (int i=0; i<Edges.size(); i++) {
        int first = Edges[i].first;
        int second = Edges[i].second;

        edges[first].push_back(second);
    }
    return solve(edges, n);
}

// Approach 2: BFS Approach

int detectCycleInDirectedGraphBFS(int n, vector<pair<int,int>> &Edges) {
    vector<vector<int>> edges(n+1); // adjacency list
    vector<int> inDegree(n+1, 0);
    // this inDegree vector maintains the number of incoming edges to the vertex.

    for (int i=0; i<Edges.size(); i++) {
        int first = Edges[i].first;
        int second = Edges[i].second;

        edges[first].push_back(second); // we put the adjacent vertex to the list.
        inDegree[second]++; // this increments the incoming edges to the vertex.
    }

    queue<int> q; // queue for the BFS

    for (int i=1; i<=n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            // push that vertex in the queue which has only outgoing edges not incoming edges.
        }
    }

    while (!q.empty()) {
        int vertex = q.front(); // take out the vertex which has no incoming edges.
        q.pop();

        for (int neighbour : edges[vertex]) { // traverse the adjacent list to particular vertex.
            inDegree[neighbour]--; 
            // decrements the incoming edge to specify that that edge is visited.
            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    for (int i=1; i<=n; i++) {
        if (inDegree[i] > 0) {
            return true; 
            // if there is cycle present in the graph, there will be atleast 
            // one vertex which is unvisited.
        }
    }

    return false; 
    // when there is no cycle is present in the graph, every vertex is visited & there is 
    // no incoming edges to the vertex.
}
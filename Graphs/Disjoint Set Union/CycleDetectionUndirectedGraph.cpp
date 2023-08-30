#include <iostream>
#include <vector>
using namespace std;

// this problem can be done with the help of DFS & BFS, but most optimal way is 
// DSU (Union Find).

int findUltimateParent(int u, vector<int> &parent) {
    if (u == parent[u]) {
        return u;
    }
    parent[u] = findUltimateParent(parent[u], parent);
    // here we are doing path compression storing the ultimate parent in parent vector.
    return parent[u];
}

string cycleDetection (vector<vector<int>>& edges, int n, int e) {
    // we are given edges as adjacency list

    // step 1: make two vectors rank and parent for DSU by rank.
    vector<int> rank(n+1, 0);
    vector<int> parent(n+1);
    for (int i=1; i<=n; i++) {
        parent[i] = i;
    }

    // step 2: go through all the edges and check for the cycle
    
    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];

        // find the ultimate parent of both

        int up_u = findUltimateParent(u, parent);
        int up_v = findUltimateParent(v, parent);

        if (up_u == up_v) { 
            // if there is edge between u & v && their ultimate parents are also equal, 
            // means cycle is detectedd and return "YES".
            return "Yes";
        }

        if (rank[up_u] < rank[up_v]) {
            parent[up_u] = up_v;
        }
        else if (rank[up_v] < rank[up_u]) {
            parent[up_v] = up_u;
        }
        else {
            parent[up_v] = up_u;
            rank[up_u]++;
        }
    }

    return "No";
}
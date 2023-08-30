#include <iostream>
#include <vector>
using namespace std;

class DisjointSetUnion {
    vector<int> rank;
    vector<int> parent;

    public:

    DisjointSetUnion(int n) {
        rank.resize(n+1, 0); // mark rank for everyone equal to 0 initially.
        parent.resize(n+1);
        for (int i=0; i<=n; i++) { // initially mark everyone parent of itself.
            parent[i] = i;
        }
    }

    int findUltimateParent(int u) {
        if (u == parent[u]) {
            return u;
        }
        return findUltimateParent(parent[u]);
    }

/*
    int findUltimateParent(int u) {
        if (u == parent[u]) {
            return u;
        }
        parent[u] = findUltimateParent(parent[u]); 
        // here we are doing the path compression
        return parent[u];
    }
*/
    void unionByRank(int u, int v) {
        int up_u = findUltimateParent(u);
        int up_v = findUltimateParent(v);

        if (up_u == up_v) {
            return;
        }

        if (rank[up_u] < rank[up_v]) { // if rank of ultimate parent of u is less than v
            parent[up_u] = up_v; // make v as parent of u
        }
        else if (rank[up_u] > rank[up_v]) { // if rank of ultimate parent of v is less than u
            parent[up_v] = up_u; // make u as parent of v
        }
        else {
            // you can do any of above but increment rank by 1
            parent[up_v] = up_u;
            rank[up_u]++; // increment the rank whenever we find the ranks of both equal.
        }
    }
};
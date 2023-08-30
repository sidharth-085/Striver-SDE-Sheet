#include <iostream>
#include <vector>
using namespace std;

class DisjointSetUnion {
    vector<int> size;
    vector<int> parent;

    public:

    DisjointSetUnion(int n) {
        size.resize(n+1, 1);
        parent.resize(n+1);
        for (int i=0; i<=n; i++) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int u) {
        if (u == parent[u]) {
            return u;
        }
        parent[u] = findUltimateParent(parent[u]); // here we are doing the path compression
        return parent[u];
    }

    void unionByRank(int u, int v) {
        int up_u = findUltimateParent(u);
        int up_v = findUltimateParent(v);

        if (up_u == up_v) {
            return;
        }

        if (size[up_u] < size[up_v]) {
            parent[up_u] = up_v;
            size[up_v] = size[up_v] + size[up_u];
        }
        else if (size[up_u] > size[up_v]) {
            parent[up_v] = up_u;
            size[up_u] = size[up_u] + size[up_v];
        }
        else {
            // you can do any of above but increment rank by 1
            parent[up_v] = up_u;
            size[up_u] = size[up_u] + size[up_v];
        }
    }
};
#include <vector>
using namespace std;

void dfsHelper(vector<vector<int>> &edges, int n, vector<bool> &visited, int startVertex, vector<int> &ans) {
    visited[startVertex] = true;
    ans.push_back(startVertex);

    for (int i=0; i<n; i++) {
        if (edges[startVertex][i] != 0 && !visited[i] && i != startVertex) {
            dfsHelper(edges, n, visited, i, ans);
        }
    }
}

vector<vector<int>> depthFirstSearch(int n, int e, vector<vector<int>> &edges) {
    // edges given as arguments hold the pairs of edges i.e. edges[i][0] & edges[i][1].
    vector<vector<int>> Edges(n, vector<int>(n, 0));

    for (int i=0; i<e; i++) {
        int first = edges[i][0];
        int second = edges[i][1];

        Edges[first][second] = 1;
        Edges[second][first] = 1;
    }

    vector<vector<int>> ans;
    vector<bool> visited(n, false);

    for (int i=0; i<n; i++) {
        vector<int> newAns;
        if (!visited[i]) {
            dfsHelper(Edges, n, visited, i, newAns);
            ans.push_back(newAns);
        }
    }
    return ans;
}
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void bfsHelper(vector<vector<int>> &edges, int n, vector<bool> &visited, vector<int> &ans, int startVertex) {
    queue<int> input;
    input.push(startVertex);
    ans.push_back(startVertex);

    visited[startVertex] = true;

    while (!input.empty()) {
        int top = input.front();
        input.pop();

        for (int i=0; i<n; i++) {
            if (i == top) {
                continue;
            }
            if (edges[top][i] == 1 && !visited[i]) {
                input.push(i);
                ans.push_back(i);
                visited[i] = true;
            }
        }
    }
}

vector<int> BFS(int n, vector<pair<int, int>> edges) {
    vector<int> ans;
    vector<vector<int>> Edges(n, vector<int>(n, 0));

    for (int i=0; i<edges.size(); i++) {
        int first = edges[i].first;
        int second = edges[i].second;
        Edges[first][second] = 1;
        Edges[second][first] = 1;
    }

    vector<bool> visited(n, false);

    for (int i=0; i<n; i++) {
        if (visited[i] == false) {
            bfsHelper(Edges, n, visited, ans, i);
        }
    }
    return ans;
}
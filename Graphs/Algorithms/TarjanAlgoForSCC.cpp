#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// This algorithm only traverse the DFS once, hence considered to be optimzed than 
// kosaraju's algorithm

int discoveryTime = 0;

void dfs(vector<vector<int>> &adjList, int startVertex, vector<int> &disc, 
    vector<int> &low, stack<int> &stk, vector<bool> &inStack, vector<vector<int>> &ans) {
    
    // mark the discovery time & lowest discovery time first
    disc[startVertex] = discoveryTime;
    low[startVertex] = discoveryTime;

    // add the startVertex to the stack
    stk.push(startVertex);
    inStack[startVertex] = true;

    // increment the discovery time
    discoveryTime++;

    // traverse all the neighbours of startVertex
    for (int neighbour : adjList[startVertex]) {
        // there can be two cases
        
        // case 1: when it is not visited yet
        if (disc[neighbour] == -1) {
            dfs(adjList, neighbour, disc, low, stk, inStack, ans);
            low[startVertex] = min(low[startVertex], low[neighbour]);
        }

        // case 2: when the current neighbour is already present in stack i.e backedge
        else if (inStack[neighbour] == true) {
            low[startVertex] = min(low[startVertex], disc[neighbour]);
            // here we are taking discover time of neighbour when it is backedge because 
            // it can be multiple edges for that visited neighbour
        }
    }

    // there will be a condition when discovery time == lowest discovery time, it indicates
    // this can be the head/root of strongly connected component because it does not contain
    // any back edge.

    // Therefor, there can be one ss component

    if (disc[startVertex] == low[startVertex]) {
        vector<int> component;
        while (stk.top() != startVertex) {
            int top = stk.top();
            stk.pop();
            inStack[top] = false;

            component.push_back(top);
        }

        int top = stk.top();
        stk.pop();
        inStack[top] = false;

        component.push_back(top);
        ans.push_back(component);
    }
}

vector<vector<int>> stronglyConnectedComponents(int n, vector<vector<int>> &edges) {
    // firstly make the adj list from given edges matrix
    vector<vector<int>> adjList(n);
    for (int i=0; i<edges.size(); i++) {
        int first = edges[i][0];
        int second = edges[i][1];

        adjList[first].push_back(second);
    }

    // step 1: make the discovery time & lowest discovery time to a node from a given node.
    vector<int> disc(n, -1); // it will be used as visited array.
    vector<int> low(n, -1);

    // make a stack for keeping the track of traversed vertices
    stack<int> stk;
    // also make a vector to store is vertex present in stack or not
    vector<bool> inStack(n, false);

    vector<vector<int>> ans;

    for (int i=0; i<n; i++) {
        if (disc[i] == -1) {
            dfs(adjList, i, disc, low, stk, inStack, ans);
        }
    }

    return ans;
}
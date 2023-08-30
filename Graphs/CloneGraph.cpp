#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

class graphNode {
public:
    int data;
    vector<graphNode*> neighbours;
    graphNode() {
        data = 0;
        neighbours = vector<graphNode*>();
    }

    graphNode(int val) {
        data = val;
        neighbours = vector<graphNode*>();
    }

    graphNode(int val, vector<graphNode*> neighbours) {
        data = val;
        this->neighbours = neighbours;
    }
};

// BFS APPROACH FOR CLONE Graph
graphNode* cloneGraphBFS(graphNode* startNode) {
    // Create a clone of the start node
    graphNode* cloneGraphNode = new graphNode(startNode->data);

    // Map to store visited original nodes and their corresponding clones
    unordered_map<graphNode*, graphNode*> visited;

    // Queue for BFS traversal
    queue<graphNode*> q;

    // Enqueue the start node
    q.push(startNode);

    // Mark the start node as visited and store its clone in the visited map
    visited[startNode] = cloneGraphNode;

    while (!q.empty()) {
        // Get the top node from the queue
        graphNode* top = q.front();
        q.pop();

        // Iterate over the neighbors of the current node
        for (int i = 0; i < top->neighbours.size(); i++) {
            graphNode* neighbour = top->neighbours[i];

            // Check if the neighbor has been visited
            if (visited.find(neighbour) == visited.end()) {
                // If not visited, enqueue the neighbor
                q.push(neighbour);

                // Create a clone of the neighbor
                graphNode* cloneNeighbour = new graphNode(neighbour->data);

                // Mark the neighbor as visited and store its clone in the visited map
                visited[neighbour] = cloneNeighbour;
            }

            // Connect the clone of the neighbor to the clone of the current node
            visited[top]->neighbours.push_back(visited[neighbour]);
        }
    }

    // Return the clone of the start node
    return cloneGraphNode;
}

// DFS APPROACH FOR CLONE Graph
graphNode* cloneGraphDFShelper(graphNode* node, unordered_map<graphNode*, graphNode*>& visited) {
    if (node == NULL) {
        return NULL;
    }

    // Check if the current node has already been visited
    if (visited.find(node) != visited.end()) {
        return visited[node];
    }

    // Create a clone of the current node
    graphNode* cloneNode = new graphNode(node->data);
    visited[node] = cloneNode;

    // Iterate over the neighbors of the current node
    for (int i=0; i<node->neighbours.size(); i++) {
        graphNode *neighbor = node->neighbours[i];
        // Recursively clone each neighbor
        graphNode* cloneNeighbor = cloneGraphDFShelper(neighbor, visited);

        // Connect the cloned neighbor to the cloned node
        cloneNode->neighbours.push_back(cloneNeighbor);
    }

    /*
    for (auto neighbor : node->neighbours) {
        // Recursively clone each neighbor
        graphNode* cloneNeighbor = cloneGraphDFShelper(neighbor, visited);

        // Connect the cloned neighbor to the cloned node
        cloneNode->neighbours.push_back(cloneNeighbor);
    }
    */

    return cloneNode;
}

graphNode* cloneGraphDFS(graphNode* startNode) {
    unordered_map<graphNode*, graphNode*> visited;
    return cloneGraphDFShelper(startNode, visited);
}
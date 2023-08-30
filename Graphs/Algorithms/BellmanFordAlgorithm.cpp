#include <iostream>
#include <vector>
using namespace std;

// Bellman Ford algorithm only valid for Directed Graphs and can work for negative
// weights also (IMP).

// We can use Bellman Ford Algorithm on Un-directed Graphs but, Bellman Ford algorithm
// can find the negative cycle in the graph and will not give answer for graph having
// negative cycles. So to apply Bellman Ford algorithm to Undirected graph, there is no
// negative cycle which means there is no edge with negative weight because due to 
// two sided directed edge with negative weight, it acts as negative cycle.

// Bellman Ford Algotithm involves some steps to calculate the shortest distance or 
// path from given source in the form of array representing every index a vertex and 
// its value as shortest distance from source to current vertex.

// Step 1: First make the distance array which stores shortest distance from source
//         to every vertex
// Step 2: Secondly, mark the distance from source to source 0 in the dist array.
// Step 3: Run the loop N-1 times which we call Relaxations. N-1 relaxations because
//         In the worst case, graph is flat so we have to check every edge which are 
//         n-1 in number. So we run n-1 itertions to calculate shortest path from every
//         vertex.
// Step 4: For every relaxation, you have to check for every edge that if path from 
//         first to second is smaller than current shortest distance for second then 
//         update the distance value for second and do till n-1 iterations. 

// Time Complexity: O(N * M)
// Space Complexity: O(N)
// N is number of vertices and M is number

vector<int> bellmonFord(int n, int m, int src, vector<vector<int>> &edges) {
    int mod = 1e8;
    
    // initially for every vertex from 1 to N, the shortest distance is mod because it
    // is not visited yet
    vector<int> dist(n + 1, mod);

    // only for src, the distance is 0.
    dist[src] = 0;

    int count = 1;
    while (count < n) { // run loop for n-1 relaxations.
        for (int i=0; i<m; i++) {
            int first = edges[i][0]; // pick out the first vertex from current edge
            int second = edges[i][1]; // pick out the second vertex from current edge
            int weight = edges[i][2]; // pick out the weight between first and second

            // if current first distance is visited (not equal to mod) only then compare
            // shortest distance from source to first + weight from first to second is
            // smaller than shortest distance from source to second. If this is true, 
            // then update the shortest distance for second

            if (dist[first] != mod && dist[first] + weight < dist[second]) {
                dist[second] = dist[first] + weight; 
            }
        }
        count++; // increase the relaxation number
    }

    // Now, in this question we can have the negative cycles, so to detect the negative 
    // cycle we can do one more relaxation i.e. nth relaxation and if path is again 
    // reducing it means it has negative cycle

    for (int i=0; i<m; i++) {
            int first = edges[i][0]; 
            int second = edges[i][1]; 
            int weight = edges[i][2]; 

            if (dist[first] != mod && dist[first] + weight < dist[second]) {
                return {-1};
                // if again the distance is reducing, return -1 array
            }
        }

    return dist;
}
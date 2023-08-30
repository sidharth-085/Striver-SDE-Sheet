#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to check if a cell is safe to visit
bool isSafe(int row, int col, int n, int m, vector<vector<bool>> &visited) {
   return (row >= 0 && row < n && col >= 0 && col < m && visited[row][col] == false);
}

// Breadth-First Search (BFS) function to explore the connected island cells
void bfs(int row, int col, int **arr, vector<vector<bool>> &visited, int n, int m) {
   int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; // Possible movements in the x-axis
   int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1}; // Possible movements in the y-axis
   
   queue<pair<int,int>> q;
   q.push({row, col});
   visited[row][col] = true;

   while (!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();

      for (int i=0; i<8; i++) {
         int newX = x + dx[i];
         int newY = y + dy[i];

         if (isSafe(newX, newY, n, m, visited) && arr[newX][newY] == 1) {
            q.push({newX, newY});
            visited[newX][newY] = true;
         }
      }
   }
}

// Depth-First Search (DFS) function to explore the connected island cells
void dfs(int row, int col, int **arr, vector<vector<bool>> &visited, int n, int m) {
/*
    we can also use the if statement to avoid the isSafe function & if block below.
    if (row < 0 || row >= n || col < 0 || col >= m || arr[row][col] == 0 || visited[row][col] == 1) {
        return;
    }   
    by this we can exclude the if statement of for loop below.
*/
    visited[row][col] = true; // Mark the current cell as visited

    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}; // Possible movements in the x-axis
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1}; // Possible movements in the y-axis

    // Explore all adjacent cells
    for (int i=0; i<8; i++) {
        int newX = row + dx[i]; // Calculate the new x-coordinate
        int newY = col + dy[i]; // Calculate the new y-coordinate

        // Check if the new cell is safe to visit and it contains an island (value = 1)
        if (isSafe(newX, newY, n, m, visited) && arr[newX][newY] == 1) {
            dfs(newX, newY, arr, visited, n, m); // Recursively call DFS on the new cell
        }
    }
}

// Function to count the total number of islands
int getTotalIslands(int** arr, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false)); // Create a visited array to track visited cells

    int count = 0; // Initialize the count of islands

    // Traverse through all cells of the given matrix
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            // If a cell contains an island (value = 1) and it has not been visited yet, perform DFS
            if (arr[i][j] == 1 && visited[i][j] == false) {
                dfs(i, j, arr, visited, n, m); // Explore the connected island cells using DFS
                count++; // Increment the count of islands
            }
        }
   }

   return count; // Return the total number of islands
}

// Using Disjoint Set Union 

// Function to find the root of a set (disjoint set)
int findRoot(vector<int>& parent, int x) {
    if (parent[x] != x)
        parent[x] = findRoot(parent, parent[x]);
    return parent[x];
}

// Function to perform union of two sets (disjoint sets)
void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int rootX = findRoot(parent, x);
    int rootY = findRoot(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Function to count the number of departments
int countDepartments(int n, vector<pair<int, int>>& related) {
    vector<int> parent(n + 1);
    vector<int> rank(n + 1, 0);

    // Initializing each person as a separate set
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    // Performing unions based on related pairs
    for (const auto& relation : related) {
        int x = relation.first;
        int y = relation.second;
        unionSets(parent, rank, x, y);
    }

    // Counting the number of disjoint sets
    int numDepartments = 0;
    for (int i = 1; i <= n; i++) {
        if (parent[i] == i) {
            numDepartments++;
        }
    }

    return numDepartments;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> related;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        related.push_back({x, y});
    }

    int numDepartments = countDepartments(n, related);
    cout << numDepartments << endl;

    return 0;
}
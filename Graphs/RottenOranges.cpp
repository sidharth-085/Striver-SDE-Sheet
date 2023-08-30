#include <iostream>
#include <queue>
using namespace std;

bool isSafe(int row, int col, int n, int m) {
    return (row >= 0 && col >= 0 && row < n && col < m);
}

// Approach without using visited grid and altering the given grid.
int minimumTimeToRotOranges(vector<vector<int>> &grid, int n, int m) {  // BFS
    queue<pair<int,int>> rottenOranges;
    int time = 0;

    // Enqueue initial rotten oranges
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 2) {
                rottenOranges.push({i, j});
            }
        }
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!rottenOranges.empty()) {
        int size = rottenOranges.size();
        bool flag = false;

        // Process the rotten oranges in the current iteration
        for (int i=0; i<size; i++) {
            int first = rottenOranges.front().first;
            int second = rottenOranges.front().second;
            rottenOranges.pop();

            // Check adjacent cells and make fresh oranges rotten
            for (int k=0; k < 4; k++) {
                int newX = first + dx[k];
                int newY = second + dy[k];

                if (grid[newX][newY] == 1 && isSafe(newX, newY, n, m)) {
                    flag = true;
                    grid[newX][newY] = 2;
                    rottenOranges.push({newX, newY});
                }
            }
        }

        if (flag == true) {
            time++; // Increment time if any new oranges got rotten
        }
    }

    // Check if any fresh orange is still remaining
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 1) {
                return -1; // Return -1 if any fresh orange is still remaining
            }
        }
    }

    return time;
}

// Approach using visited grid to not alter the grid given as an argument.
int minimumTimeToRotOranges(vector<vector<int>> &grid, int n, int m) {  // BFS
    int freshCount = 0;
    queue<pair<pair<int,int>, int>> rottenOranges;
    int minTime = 0;

    // Create a visited grid to keep track of visited cells
    vector<vector<int>> visited(n, vector<int>(m, 0));

    // Enqueue initial rotten oranges and count fresh oranges
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 2) {
                rottenOranges.push({{i, j}, 0});
                visited[i][j] = 2;
            }
            if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    int currentFreshCount = 0;

    while (!rottenOranges.empty()) {
        int first = rottenOranges.front().first.first;
        int second = rottenOranges.front().first.second;

        int time = rottenOranges.front().second;
        if (time > minTime) {
            minTime = time;
        }

        rottenOranges.pop();

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        // Check adjacent cells and make fresh oranges rotten
        for (int k=0; k<4; k++) {
            int newX = first + dx[k];
            int newY = second + dy[k];

            if (isSafe(newX, newY, n, m) && grid[newX][newY] == 1 && visited[newX][newY] != 2) {
                rottenOranges.push({{newX, newY}, time+1});
                visited[newX][newY] = 2;
                currentFreshCount++;
            }
        }
    }

    // Check if any fresh orange is still remaining
    if (currentFreshCount != freshCount) {
        return -1; // Return -1 if any fresh orange is still remaining
    }

    return minTime;
}
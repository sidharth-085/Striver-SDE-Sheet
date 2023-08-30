#include <vector>
using namespace std;

// For more approaches, go to backtracking folder.
// Here we are printing the path.

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isSafe(int row, int col, vector<vector<int>> &maze, vector<vector<int>> &visited, int n) {
  return (row >=0 && row < n && col >= 0 && col < n && maze[row][col] == 1 && visited[row][col] == 0);
}

void solve(int row, int col, int n, vector<vector<int>> &maze, vector<vector<int>> &visited, vector<vector<int>> &ans) {
  if (row == n-1 && col == n-1) {
    visited[row][col] = 1;
   
    vector<int> path;

    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
        path.push_back(visited[i][j]);
      }
    }

    ans.push_back(path);

    visited[row][col] = 0;
    return;
  }

  visited[row][col] = 1;

  for (int i=0; i<4; i++) {
    int newX = row + dx[i];
    int newY = col + dy[i];

    if (isSafe(newX, newY, maze, visited, n)) {
      solve(newX, newY, n, maze, visited, ans);
    }
  }

  visited[row][col] = 0;

}

vector<vector<int>> ratInAMaze(vector<vector<int>> &maze, int n) {
  vector<vector<int>> visited(n, vector<int>(n, 0));
  vector<vector<int>> ans;
  vector<int> path;
  solve(0, 0, n, maze, visited, ans);
  return ans;
}
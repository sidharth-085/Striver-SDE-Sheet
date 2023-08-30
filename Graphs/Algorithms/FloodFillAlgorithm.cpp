#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isSafe(vector<vector<int>> &image, int x, int y, int n, int m, int color, int newColor) {
    return (x >= 0 && x < n && y >= 0 && y < m && image[x][y] == color && image[x][y] != newColor);
}

void dfs(vector<vector<int>> &image, int x, int y, int color, int newColor) {
    int n = image.size();
    int m = image[0].size();

    if (isSafe(image, x, y, n, m, color, newColor)) {
        image[x][y] = newColor;

        dfs(image, x-1, y, color, newColor);
        dfs(image, x+1, y, color, newColor);
        dfs(image, x, y-1, color, newColor);
        dfs(image, x, y+1, color, newColor);
    }
}

void bfs(vector<vector<int>> &image, int x, int y, int color, int newColor) {
    int n = image.size();
    int m = image[0].size();
    
    queue<pair<int,int>> q;
    q.push({x, y});

    while (!q.empty()) {
        pair<int,int> front = q.front();
        q.pop();

        int first = front.first;
        int second = front.second;

        if (isSafe(image, first, second, n, m, color, newColor)) {
            image[first][second] = newColor;
            
            q.push({first - 1, second});
            q.push({first + 1, second});
            q.push({first, second - 1});
            q.push({first, second + 1});
        }
    }
} 

vector<vector<int>> floodFill(vector<vector<int>> &image, int x, int y, int newColor) {
    int color = image[x][y];
    dfs(image, x, y, color, newColor);
    return image;
}
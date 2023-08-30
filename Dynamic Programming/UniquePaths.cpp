#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int row, int col, int n, int m) {
	return (row >= 0 && row < n && col >= 0 && col < m);
}

// Brute Force Recursion Approach: whenever we reached at final destination we increment
// numPaths by 1.

// Time Complexity: O(2^(N+M))
// Space Complexity: O(max(N, M)) [Due to recursion stack]
// N is number of rows
// N is number of cols

void uniquePaths(int row, int col, int n, int m, int &numPaths) {
	if (row == n - 1 && col == m - 1) {
		numPaths++; // whenever we reached to destination increment numPaths
		return;
	}

	if (isSafe(row+1, col, n, m)) { // right direction
		uniquePaths(row+1, col, n, m, numPaths); // if right direction is safe, call recursion
	}

	if (isSafe(row, col+1, n, m)) { // downward direction
		uniquePaths(row, col+1, n, m, numPaths); // if down direction is safe, call recursion.
	}
}

int uniquePaths(int n, int m) {
	int numPaths = 0;
	uniquePaths(0, 0, n, m, numPaths); // pass numPaths as reference
	return numPaths;
} 

// Optimized Brute Force: Memoization Approach

// Time Complexity: O(M * N)
// Space Complexity: O(N*M) (due to memoization grid)

int uniquePaths(int row, int col, int n, int m, vector<vector<int>> &ans) {
    // altered this function for applying memoization correctly
	if (row == n - 1 && col == m - 1) {
		return 1;
	}

	if (ans[row][col] != -1) {
		return ans[row][col];
	}

	int option1 = 0, option2 = 0;
	if (isSafe(row+1, col, n, m)) {
		option1 = uniquePaths(row+1, col, n, m, ans);
	}

	if (isSafe(row, col+1, n, m)) {
		option2 = uniquePaths(row, col+1, n, m, ans);
	}

	ans[row][col] = option1 + option2;
    // add both num of paths from option1 and option2
    return ans[row][col];
}

int uniquePaths(int n, int m) {
	vector<vector<int>> ans(n+1, vector<int>(m+1, -1));
	return uniquePaths(0, 0, n, m, ans);
}

// Optimized DP Solution
// Time Complexity: O(N*M)

// Space Complexity: O(N*M)

int uniquePaths(int n, int m) {
	vector<vector<int>> ans(n, vector<int>(m));
    // Dp grid

	for (int i=0; i<m; i++) { // if row is one, only one path is possible for every col.
		ans[0][i] = 1;
	}

	for (int i=0; i<n; i++) { // if col is one, only one path is possible for every row.
		ans[i][0] = 1;
	}

	for (int i=1; i<n; i++) {
		for (int j=1; j<m; j++) {
			ans[i][j] = ans[i-1][j] + ans[i][j-1];
            // add both to get total number of paths
		}
	}
	return ans[n-1][m-1];
}

// Space Optimized DP approach
// Time Complexity: O(N*M)

// Space Complexity: O(N)

int uniquePaths(int n, int m) {
    vector<int> ans(m, 0); 

    ans[0] = 1; // if column is only 1, only one path is possible
    for (int i = 0; i < n; i++) { // run loop from 0 to n-1 for rows
        for (int j = 1; j < m; j++) { // run loop from 1 to m-1 for cols
            ans[j] = ans[j] + ans[j-1];
            // ans[j] is denoting the downward direction as row varies but col remains same
            // ans[j-1] is denoting the upward direction as col varies but row remains same
        }
    }

    return ans[m-1]; // finally return destination which is last col m-1.
}
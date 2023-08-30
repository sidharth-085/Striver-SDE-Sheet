#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to check if a cell is within the grid boundaries
bool isSafe(int row, int col, int m, int n) {
    if (row >= 0 && row < m && col >= 0 && col < n) {
        return true;
    }
    return false;
}

// BRUTE FORCE APPROACH

// Recursive function to calculate the minimum cost path
int solve(int row, int col, int **input, int m, int n) { // BRUTE FORCE APPROACH
    // Base case: reached the bottom-right cell
    if (row == m - 1 && col == n - 1) {
        return input[row][col];
    }

    int option1 = INT_MAX, option2 = INT_MAX, option3 = INT_MAX;

    // Check if moving down is a valid move
    if (isSafe(row + 1, col, m, n)) {
        option1 = solve(row + 1, col, input, m, n);
    }

    // Check if moving right is a valid move
    if (isSafe(row, col + 1, m, n)) {
        option2 = solve(row, col + 1, input, m, n);
    }

    // Check if moving diagonally is a valid move
    if (isSafe(row + 1, col + 1, m, n)) {
        option3 = solve(row + 1, col + 1, input, m, n);
    }

    // Calculate the minimum cost among the three options and add the current cell's value
    int minCost = min(option1, min(option2, option3)) + input[row][col];
    return minCost;
}

// Function to find the minimum cost path using the solve function
int minCostPath(int **input, int m, int n) { // BRUTE FORCE APPROACH
    return solve(0, 0, input, m, n);
}

// USING MEMOIZATION METHOD

// Recursive function to calculate the minimum cost path using memoization
int solveUsingMemoization(int row, int col, int **input, int m, int n, vector<vector<int>> &ans) {
    // Base case: reached the bottom-right cell
    if (row == m - 1 && col == n - 1) {
        return input[row][col];
    }

    // Check if the subproblem has already been solved and return the stored result
    if (ans[row][col] != -1) {
        return ans[row][col];
    }

    int option1 = INT_MAX, option2 = INT_MAX, option3 = INT_MAX;

    // Check if moving down is a valid move
    if (isSafe(row + 1, col, m, n)) {
        option1 = solveUsingMemoization(row + 1, col, input, m, n, ans);
    }

    // Check if moving right is a valid move
    if (isSafe(row, col + 1, m, n)) {
        option2 = solveUsingMemoization(row, col + 1, input, m, n, ans);
    }

    // Check if moving diagonally is a valid move
    if (isSafe(row + 1, col + 1, m, n)) {
        option3 = solveUsingMemoization(row + 1, col + 1, input, m, n, ans);
    }

    // Calculate the minimum cost among the three options and add the current cell's value
    int minCost = min(option1, min(option2, option3)) + input[row][col];

    // Store the result in the memoization table for future use
    ans[row][col] = minCost;

    return minCost;
}

// Function to find the minimum cost path using memoization
int minCostPathUsingMemoization(int **input, int m, int n) {
    // Create a memoization table to store intermediate results
    vector<vector<int>> ans(m, vector<int>(n, -1));

    // Call the solve function with memoization
    return solveUsingMemoization(0, 0, input, m, n, ans);
}

// Dynamic Programming Approach 1
// This function calculates the minimum cost path using dynamic programming.
// It starts from the bottom-right corner and iteratively fills the 'ans' matrix with 
// the minimum cost values.
// The final result is the minimum cost value at the top-left corner of the 'ans' matrix.

int minCostPathUsingDP1(int **input, int m, int n) {
    // Create a matrix to store the minimum cost values
    vector<vector<int>> ans(m, vector<int>(n, 0));

    // Initialize the bottom-right cell with its cost
    ans[m - 1][n - 1] = input[m - 1][n - 1];

    // Fill the bottom row of the 'ans' matrix
    for (int i = n - 1; i > 0; i--) {
        ans[m - 1][i - 1] = input[m - 1][i - 1] + ans[m - 1][i];
    }

    // Fill the rightmost column of the 'ans' matrix
    for (int i = m - 1; i > 0; i--) {
        ans[i - 1][n - 1] = input[i - 1][n - 1] + ans[i][n - 1];
    }

    // Fill the remaining cells of the 'ans' matrix
    for (int i = m - 1; i > 0; i--) {
        for (int j = n - 1; j > 0; j--) {
            ans[i - 1][j - 1] = min(ans[i - 1][j], min(ans[i][j - 1], ans[i][j])) + input[i - 1][j - 1];
        }
    }

    // Return the minimum cost at the top-left corner of the 'ans' matrix
    return ans[0][0];
}

// Dynamic Programming Approach 2
// This function calculates the minimum cost path using dynamic programming.
// It starts from the top-left corner and iteratively fills the 'ans' matrix with the 
// minimum cost values.
// The final result is the minimum cost value at the bottom-right corner of the 'ans' 
// matrix.

int minCostPathUsingDP2(int **input, int m, int n) {
    // Create a matrix to store the minimum cost values
    vector<vector<int>> ans(m, vector<int>(n, 0));
    
    // Initialize the top-left cell with its cost
    ans[0][0] = input[0][0];

    // Fill the first column of the 'ans' matrix
    for (int i = 1; i < m; i++) {
        ans[i][0] = ans[i - 1][0] + input[i][0];
    }

    // Fill the first row of the 'ans' matrix
    for (int i = 1; i < n; i++) {
        ans[0][i] = ans[0][i - 1] + input[0][i];
    }

    // Fill the remaining cells of the 'ans' matrix
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            ans[i][j] = min(ans[i - 1][j], min(ans[i][j - 1], ans[i - 1][j - 1])) + input[i][j];
        }
    }

    // Return the minimum cost at the bottom-right corner of the 'ans' matrix
    return ans[m - 1][n - 1];
}

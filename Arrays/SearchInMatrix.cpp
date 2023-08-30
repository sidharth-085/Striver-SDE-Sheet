#include <iostream>
#include <vector>
using namespace std;

// Every Row of matrix is given in sorted order

// Approach using Nested Loops
// Time Complexity: O(N^2)
// Space Complexity: O(1)

bool searchMatrix(vector<vector<int>>& mat, int target) {
    for (int i=0; i<mat.size(); i++) { // check for every row
        for (int j=0; j<mat[i].size(); j++) {
            if (target == mat[i][j]) {
                return true;
            }
        }
    }

    return false; // if not found return false.
}

// Approach using Binary Search
// Time Complexity: O(N * Log M)
// Space Complexity: O(1)
// N & M total number of rows and cols

bool binarySearch(vector<int> &arr, int start, int end, int target) { // recursive binary search
    // search from start to end by doing binary search
    if (start > end) {
        return false;
    }

    int mid = start + (end-start)/2;

    if (arr[mid] == target) { // if found return true
        return true;
    }

    else if (arr[mid] > target) { // if target is less than mid, check left
        return binarySearch(arr, start, mid-1, target);
    }
    else { // if target is more than mid, check right
        return binarySearch(arr, mid+1, end, target);
    }
}

bool searchMatrix(vector<vector<int>>& mat, int target) {
    for (int i=0; i<mat.size(); i++) { // check for every row
        bool ans = binarySearch(mat[i], 0, mat[i].size()-1, target);
        if (ans == true) {
            return true;
        }
    }

    return false; // if not found return false.
}
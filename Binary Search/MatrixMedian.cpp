#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

// Approach 1: Brute Force: Make a single list, insert all elements and sort to get median
// Time Complexity: O(N * M * Log(N * M))
// Space Complexity: O(N * M)

int getMedian(vector<vector<int>> &matrix) {
    vector<int> arr;

    for (int i=0; i < matrix.size(); i++) {
        for (int j=0; j < matrix[i].size(); j++) {
            arr.push_back(matrix[i][j]);
        }
    }

    sort(arr.begin(), arr.end());

    if (arr.size() % 2 == 0) {
        int first = arr[(arr.size() - 1)/2];
        int second = arr[((arr.size() - 1)/2) + 1];
        return (first + second)/2;
    }

    return arr[(arr.size() - 1)/2];
}

// Approach 2: Using Binary Search

// Time Complexity: O(N * Log M * log(max-min))
// O(N) due to loop from 0 to N-1, O(LogM) due to upper bound && Log(max-min) due to 1 
// to 10000 traversal

int upper_bound(vector<int> const &arr, int first, int last, int val) {
    // Initialise the "low" and "high" appropriately.
    int low = first, high = last;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] > val)
        {
            /*
               If the current element is less than val,
               reduce the search space to left half.
            */
            high = mid-1;
        }
        else
        {
            /*
               If the current element is greater than or equal to val,
               reduce the search space to right half.
            */
            low = mid + 1;
        }
    }

    return low;
}

int getMedian(vector<vector<int>> &matrix) {

    int n = matrix.size();
    int m = matrix[0].size();

    // Since, 1 <= matrix[i][j] <= 10^5, set the "low" and "high" value accordingly.
    int low = 1, high = 100000;

    // Loop until our search spaces convergers to single element.
    while (low < high)
    {

        int mid = (low + high) / 2;

        // To count number of elements less than or equal to "mid".
        int count = 0;

        // Iterate through each row and increment the "count".
        for (int i = 0; i < n; i++)
        {
            /*
               NOTE:
               upper_bound (ForwardIterator first, ForwardIterator last, const T& val);
               Returns an iterator
               pointing to the first element in the range [first,last)
               which compares greater than val.
            */
            count = count + upper_bound(matrix[i], 0, matrix[i].size()-1, mid);
        }

        if (count >= (n * m + 1) / 2)
        {
            // The median will lie in the range of [“mid”, “high”].
            high = mid;
        }
        else
        {
            // The median will lie in the range of ["mid" + 1, "high"].
            low = mid + 1;
        }
    }
    return low;
}
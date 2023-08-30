#include <queue>
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Approach using nested Loops
 /*
    Time complexity: O(N^2)
    Space complexity: O(1)

    Where  ‘N’ is the size of the given array.
*/

vector<int> kthSmallLarge(vector<int> &arr, int n, int k)
{
    // kth smallest and largest element.
    int kSmall, kLarge;

    for(int i = 0; i < max(k, n-k+1); i++) {
        // Index of smallest element.
        int minIndex = 0; 

        // Finding Index of the smallest element of array.
        for(int j = 0; j < n; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j; 
            }
        }

        if(i == k-1) { 
            // kth smallest element
            kSmall = arr[minIndex]; 
        }

        if(i == n-k) {
            // kth largest element
            kLarge = arr[minIndex]; 
        }

        // Replace by infinite value.
        arr[minIndex] = INT_MAX;    
    }

    vector<int> result = {kSmall, kLarge};
    return result;
} 

// Approach using Sorting 
// Time Complexity: O(n*Logn) & Space Complexity : O(1)

vector<int> kthSmallLarge(vector<int> &arr, int n, int k) {
    sort(arr.begin(), arr.end());

    int kSmallest = arr[k-1];
    int kLargest = arr[n-k];

    vector<int> ans = {kSmallest, kLargest};
    return ans;
}

// Approach Using Heap: (Time Complexity: O(n + k*logn) & Space Complexity: O(n)).

vector<int> kthSmallLarge(vector<int> &arr, int n, int k) {
	priority_queue<int> max;
	priority_queue<int, vector<int>, greater<int>> min;

	for (int i=0; i<n; i++) {
		max.push(arr[i]);
		min.push(arr[i]);
	}

	for (int i=0; i<k-1; i++) {
		max.pop();
		min.pop();
	}
	
	vector<int> ans;
	ans.push_back(min.top());
	ans.push_back(max.top());

	return ans;
}

// Optimal Approach using Quick-Select Algorithm (similar to Quick Sort) 
// This algo used to find kth smallest element.

// Time Complexity : O(N)
// Space Complexity : O(1)

int partition(vector<int> &arr, int low, int high) {
    int i = low;
    int pivot = arr[high]; // Choose the pivot as the last element
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]); // Swap elements smaller than or equal to pivot to the left side
            i++;
        }
    }
    swap(arr[i], arr[high]); // Move the pivot element to its correct position
    return i; // Return the index of the pivot element
}

int quickSelect(vector<int> &arr, int low, int high, int k) {
    if (low == high) {
        return arr[low]; // Base case: only one element left, return it
    }

    int partitionIndex = partition(arr, low, high); // Partition the array around a pivot

    if (k == partitionIndex + 1) {
        return arr[partitionIndex]; // Found the kth smallest element
    }
    else if (k < partitionIndex + 1) {
        return quickSelect(arr, low, partitionIndex - 1, k); // Search in the left partition
    }
    else {
        return quickSelect(arr, partitionIndex + 1, high, k); // Search in the right partition
    }
}

vector<int> kthSmallLarge(vector<int> &arr, int n, int k) {
    int kSmallest = quickSelect(arr, 0, n - 1, k); // Find the kth smallest element
    int kLargest = quickSelect(arr, 0, n - 1, n - k + 1); // Find the kth largest element

    vector<int> ans;
    ans = {kSmallest, kLargest};
    return ans;
}
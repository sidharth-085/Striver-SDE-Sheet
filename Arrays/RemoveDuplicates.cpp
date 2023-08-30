#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// sorted array is given

// Approach 1: Using Hashset
// Time Complexity: O(N)
// Space Complexity: O(N)

int removeDuplicates(vector<int> &arr, int n) {
    unordered_set<int> set;

    for (int i=0; i<n; i++) {
        set.insert(arr[i]);
    }

    return set.size();
}

// Approach 2: Without any extra space
// Time Complexity: O(N)
// Space Complexity: O(1)

int removeDuplicates(vector<int> &arr, int n) {
	int count = 0;
	int start = 0;

	for (int i = 0; i < n; i++) {
		while (i < n-1 && arr[i] == arr[i + 1]) { // skip duplicates 
			i++;
		}
		count++;
	}

	return count;
}

// Approach 3: Two Pointer Approach
// Time Complexity: O(N)
// Space Complexity: O(1)

int removeDuplicates(vector<int> &arr, int n) {
    // First pointer.
    int i = 0;

    // Second pointer traversing from 1 to n.
    for (int j = 1; j < n; j++) {
        //  If not duplicates increment first pointer and check again.
        if (arr[j] != arr[j-1]) {
            arr[i] = arr[j];
            i++;
        }
    }
    // Return length == (index of first pointer when second reaches end) + 1.
    return i + 1;
}
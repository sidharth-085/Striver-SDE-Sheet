#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force
// Time Complexity  : O(N)
// Space Complexity : O(1)

int singleNonDuplicate(vector<int>& arr) {
    int n = arr.size();
    int answer;

    if (n == 1) {
        return arr[0];
    }

    for (int i=0; i<n-1; i=i+2) {
        // If adjacent elements are not equal then update answer
        if (arr[i] != arr[i + 1]) {
            answer = arr[i];
            break;
        }
    }

    // Update answer
    if (arr[n - 2] != arr[n - 1]) {
        answer = arr[n - 1];
    }

    return answer;
}

// Approach 2: Using Hashmap
// Time Complexity: O(N)
// Space Complexity: O(N)

int singleNonDuplicate(vector<int>& arr) {
    // Declare a hashMap
    unordered_map<int, int> hashMap;

    // Store frequency of elements of array in hashMap
    for (int i = 0; i < arr.size(); i++) {
        hashMap[arr[i]]++;
    }

    // Find the element having frequency equal to 1 and return it
    for (auto key : hashMap) {
        if (key.second == 1) {
            return key.first;
        }
    }
}

// Approach 3: Bit Manupulation
// Time Complexity: O(N)
// Space Complexity: O(1)

int singleNonDuplicate(vector<int>& arr) {
    // Declare a variable to store answer and intialize its value to zero.
    int answer = 0;

    // Do xor of all elements and store the result in answer
    for (int element : arr) {
        answer = answer ^ element; 
        // XOR is same elements is 0, so when we take Xor of every element, only unique 
        // will left
    }

    return answer;
}

// Approach 4: Using Binary Search
// Time Complexity: O(LogN)
// Space Complexity: O(1)

// we will check the next traversal by looking at mid index
// If mid index is odd, and element next to it is same, then there are odd number of 
// elements before mid index, means unique element should be in left.

// If mid index is even, and element next to it is same, then there are even number of 
// elements before mid index, means unique elements should be in right.

int binarySearch(vector<int> &arr, int start, int end) {
	if (start > end) {
		return -1;
	}

	if (start == end) {
		return arr[start];
	}

	int mid = start + (end - start)/2;
	
	if (mid % 2 == 0) {
		if (arr[mid] == arr[mid+1]) {
			return binarySearch(arr, mid+1, end);
		}
		else {
			return binarySearch(arr, start, mid);
		}
	}
	else {
		if (arr[mid] == arr[mid+1]) {
			return binarySearch(arr, start, mid);
		}
		else {
			return binarySearch(arr, mid+1, end);
		}
	}
}

int singleNonDuplicate(vector<int>& arr) {
	return binarySearch(arr, 0, arr.size() - 1);
}
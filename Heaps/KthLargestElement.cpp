#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

// Given an unsorted array and we have to find the kth largest element
// It is very basic question on Max heaps

// Brute Force: Sort the array and get the (size-k)th element which is kth largest element
// Time complexity: O(N*Logn)
// Space Complexity: O(1)

int kthLargest(vector<int>& arr, int size, int k) {
	sort(arr.begin(), arr.end());

	return arr[size-k];
}

// This is solution with Max heap
// Time Complexity: O(N)
// Space Complexity: O(N)

int kthLargest(vector<int>& arr, int size, int k) {
	priority_queue<int> pq;
	for (int i=0; i<size; i++) {
		pq.push(arr[i]);
	}

	for (int i=0; i<k-1; i++) {
		pq.pop();
	}

	return pq.top();
}
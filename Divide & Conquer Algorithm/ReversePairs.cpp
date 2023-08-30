#include <iostream>
#include <vector>
using namespace std;

// Given an array arr, calculate the number of reverse pairs 
// A reverse pair is a pair when i < j and arr[i] > 2*arr[j].

// Brute Force Approach: Check for every element and match the condition
// Time Complexity: O(N^2)

int reversePairs(vector<int> &arr, int n){
	int count = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (arr[i] > 2*arr[j] && i < j) {
				count++;
			}
		}
	}
	return count;
}

// Optimal Approach: Modified Merge Sort Function
// Time Complexity: O(N*Log N)
// Space Complexity: O(N)

int mergeTwoSortedArrays(vector<int> &arr, int left, int mid, int right) {
	vector<int> newArr;
	int count = 0;

	// now we will check is reverse pairs are available or not
	// we have two sorted arrays now, left to mid && mid+1 to right.

	int i = left; int j = mid+1;
	while (i <= mid && j <= right) {
		if (arr[i] > 2*arr[j]) {
			// this means if arr[i] is greater then, from i to mid all are greater than
			// 2*arr[j] because array is sorted from left to mid.
			count = count + (mid - i + 1);
			j++;
		}
		else {
			i++; // if condition is not satisfied, then move to next element.
		}
	}

	// now just merge the both sorted arrays
	i = left; j = mid+1; int k = 0;
	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) {
			newArr.push_back(arr[i]);
			i++;
		}
		else {
			newArr.push_back(arr[j]);
			j++;
		}
	}

	while (i <= mid) {
		newArr.push_back(arr[i]);
		i++;
	}

	while (j <= right) {
		newArr.push_back(arr[j]);
		j++;
	} 
	
	// now new sorted array is here merged, just copy it into orignal array.

	for (int i=0; i<newArr.size(); i++) {
		arr[left + i] = newArr[i];
	}

	return count;
}

int mergeSortAndCount(vector<int> &arr, int left, int right) {
    if (left >= right) {
        return 0;
    }

	int count = 0;
	int mid = left + (right - left)/2;

	int firstHalf = mergeSortAndCount(arr, left, mid);
	int secondHalf = mergeSortAndCount(arr, mid+1, right);
	count = count + firstHalf + secondHalf + mergeTwoSortedArrays(arr, left, mid, right);
	
	return count;
}

int reversePairs(vector<int> &arr, int n) {
	return mergeSortAndCount(arr, 0, n-1);
}
#include <iostream>
using namespace std;

// This question is same as Reverse Pairs just condition is arr[i] > arr[j] && i < j

// Brute Force Approach: Nested Loops

// Brute Force Approach: Check for every element and match the condition
// Time Complexity: O(N^2)

long long reversePairs(long long *arr, int n){
	long long  count = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (arr[i] > arr[j] && i < j) {
				count++;
			}
		}
	}
	return count;
}

// Optimal Approach: Modified Merge Sort Function
// Time Complexity: O(N*Log N)
// Space Complexity: O(N)

long long modifiedMergeSort(long long *arr, int start, int mid, int end) {
    int i = start;
    int j = mid+1;

    long long newArr[end-start+1];
    int count = 0;

    while (i <= mid && j <= end) { 
        // start from start && mid+1, and count in both sorted arrays 
        // (start to mid) && (mid+1 to end)

        if (arr[i] > arr[j]) {
            // this means if arr[i] is greater then, from i to mid all are greater than
			// arr[j] because array is sorted from left to mid.
            count = count + (mid - i + 1);
            j++;
        }
        else {
            i++; // else check for next element
        }
    }

    i = start;
    j = mid+1;
    int k = 0;
    
    // now just merge the both sorted arrays
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            newArr[k] = arr[i];
            i++;
            k++;
        }
        else {
            newArr[k] = arr[j];
            j++;
            k++;
        }
    }

    while (i <= mid) {
        newArr[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end) {
        newArr[k] = arr[j];
        j++;
        k++;
    }

    for (int i=0; i<k; i++) { // copy the new sorted array to given array.
        arr[start+i] = newArr[i];
    }

    return count;
}

long long mergeSortAndCount(long long *arr, int start, int end) {
    if (start >= end) {
        return 0;
    }

    long long count = 0;
    
    int mid = start + (end-start)/2;

    count = count + mergeSortAndCount(arr, start, mid); 
    // add the pairs of sorted array from start to mid

    count = count + mergeSortAndCount(arr, mid+1, end);
    // add the pairs of sorted array from mid + 1 to end
    
    count = count + modifiedMergeSort(arr, start, mid, end); 
    // add the pairs of final sorted array and merge it.

    return count;
}

long long getInversions(long long *arr, int n) {
    return mergeSortAndCount(arr, 0, n-1);   
}
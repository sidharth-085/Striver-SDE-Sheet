#include <iostream>
using namespace std;

// Brute Force Approach: Linear Search

// Time Complexity: O(N)
// Space Complexity: O(1)

int search(int* arr, int n, int key) {
    if (n == 0) {
        return -1;
    }

    for (int i=0; i<n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }

    return -1;
}

// Approach 2: Using Binary Search 
// Time Complexity: O(N) (linear search for index of rotation)
// Space Complexity: O(1)

int binarySearch(int *arr, int left, int right, int key) { // binary search func
    int start = left;
    int end = right;

    while (start <= end) {
        int mid = start + (end - start)/2;

        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] > key) {
            end = mid-1;
        }
        else {
            start = mid+1;
        }
    }

    return -1;
}

int search(int* arr, int n, int key) {
    if (n == 0) {
        return -1;
    }

    int index = -1;
    for (int i=0; i<n-1; i++) { // search for index at which rotation is done
        if (arr[i] > arr[i+1]) {
            index = i;
            break;
        }
    }

    if (index == -1) { // if array is sorted just find the key in it using Binary search.
        return binarySearch(arr, 0, n-1, key);
    }
    else { // if not, find in both halfs
        int firstHalf = binarySearch(arr, 0, index, key); 
        // search in first half (0 to index)
        if (firstHalf != -1) {
            return firstHalf;
        }

        // search in second half (index+1 to n-1)
        int secondHalf = binarySearch(arr, index+1, n-1, key);
        if (secondHalf != -1) {
            return secondHalf;
        }
    }

    return -1; // if not found, return -1.
}

// Approach 3: Optimal Binary Search in finding the correct location

// Time Complexity: O(Log N)
// Space Complexity: O(1)

int search(int* arr, int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // find mid

        if (arr[mid] == key) { // if found at mid, return mid
            return mid;
        }
        else if (arr[left] <= arr[mid]) { 
            // if left element is smaller than mid element, then Left half is sorted
            if (key >= arr[left] && key < arr[mid]) {
                // If key lies in the left half, search it
                return binarySearch(arr, left, mid - 1, key);
            } 
            else {
                // Otherwise, search in the right half
                left = mid + 1;
            }
        } 
        else {
            // Right half is sorted
            if (key > arr[mid] && key <= arr[right]) {
                // If key lies in the right half, search it
                return binarySearch(arr, mid + 1, right, key);
            } else {
                // Otherwise, search in the left half
                right = mid - 1;
            }
        }
    }

    return -1;
}
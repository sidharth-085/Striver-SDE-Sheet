#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Brute Force Approach: Check for every element, is there exists next element of it
// we can use (linear search or binary search for searching)

// Time Complexity: O(N^3) (for linear search use)
// Time Complexity: O(N*N * Log N) (for binary search use)

// Space Complexity: O(1)

bool linearSearch(vector<int> &arr, int n, int value) { 
    // this search the element using Linear Search
    for (int i=0; i<n; i++) {
        if (arr[i] == value) {
            return true;
        }
    }

    return false;
}

bool binarySearch(vector<int> &arr, int start, int end, int value) { // iterative BS
    while (start <= end) {
        int mid = start + (end - start)/2;

        if (arr[mid] == value) {
            return true;
        }
        else if (arr[mid] > value) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return false;
}

int lengthOfLongestConsecutiveSequence(vector<int> &arr, int n) {
    int maxLength = 0;

    for (int i=0; i < n; i++) {
        // search is it starting element of the sequence
        if (linearSearch(arr, n, arr[i] - 1) == false) {
            int currElement = arr[i];
            int currLen = 1;

            // now search the next elements till not found
            while (linearSearch(arr, n, currElement + 1) == true) {
                currElement++;
                currLen++;
            }

            if (currLen > maxLength) { // update the maxLength.
                maxLength = currLen;
            }
        }
    }

    return maxLength;
}

// Better Approach using Sorting: Sort the elements and just traverse the array.

// Time Complexity: O(N * Log N)
// Space Complexity: O(1)

int lengthOfLongestConsecutiveSequence(vector<int> &arr, int n) {
    // step 1: sort the array

    sort(arr.begin(), arr.end());

    // step 2: traverse the array and count the maxLength

    int maxLen = 0;
    int currLen = 1;

    for (int i=0; i<n; i++) {
        if (i > 0 && arr[i-1] + 1 == arr[i]) { 
        // check if (previous element + 1) = current Element
            currLen++;
        }
        else if (i > 0 && arr[i-1] == arr[i]) {
            // if duplicate elements is there, skip the step.
            continue;
        }
        else {
            currLen = 1; // if (prev + 1) != current, update the curr len to 1
        }

        if (currLen > maxLen) { // now update the maxLen with currLen
            maxLen = currLen;
        }
    }

    return maxLen;
}

// Optimal Approach: Using Hashtable
// Time Complexity: O(N)
// Space Complexity: O(N)

int lengthOfLongestConsecutiveSequence(vector<int> &arr, int n) {
    unordered_map<int, int> numMap;

    int maxLength = 0;

    // step 1: insert all elements of arr in map

    for (int i=0; i<n; i++) {
        numMap[arr[i]]++;
    }

    // step 2: now traverse all elements in arr & count for max length

    for (int i=0; i<n; i++) {
        // check is arr[i] is start of the sequence

        if (numMap.find(arr[i] - 1) == numMap.end()) {
            // check if element smaller than curr one exists in map or not.
            int currElement = arr[i];
            int currLen = 1;

            // run loop and found the every next element in map
            while (numMap.find(currElement + 1) != numMap.end()) {
                currElement++;
                currLen++;
            }

            if (currLen > maxLength) { // now check is currLen is bigger than maxLength
                maxLength = currLen;
            }
        }
    }

    return maxLength; // return maxLength
}
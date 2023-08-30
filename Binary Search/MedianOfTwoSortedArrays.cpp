#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Extreme Brute Force by Sorting Algorithm
// Time Complexity: O((N+M) * Log(N+M))
// Space Complexity: O(N+M)

double median(vector<int>& arr1, vector<int>& arr2) {
    vector<int> merged; // final merged array

    int n = arr1.size();
    int m = arr2.size();

    for (int i=0; i<n; i++) { // add all elements of arr1 to merged
        merged.push_back(arr1[i]);
    }

    for (int i=0; i<m; i++) { // add elements of arr2 to merged
        merged.push_back(arr2[i]);
    }

    sort(merged.begin(), merged.end());
    // sort the merged array

    // just find the median of merged array after sorting

    int size = n + m;
    int pos = size-1;

    if (size % 2 == 0) { // if even size, take average of both mids
        double median = (merged[pos/2] + merged[(pos/2) + 1])/2.0;
        return median;
    }
    else { // if odd size, take pos/2 element.
        int median = merged[pos/2];
        return median;
    }

    return 0.0;
}

// Approach 2: Brute Force using Two Pointer (merge both arrays and find its median)

// Time Complexity: O(N+M)
// Space Complexity: O(N + M)

double median(vector<int>& arr1, vector<int>& arr2) {
    // step 1: merge two sorted arrays 
    vector<int> newArr;
    int i = 0;
    int j = 0;

    int n = arr1.size();
    int m = arr2.size();

    while (i < n && j < m) {
        if (arr1[i] < arr2[j]) {
            newArr.push_back(arr1[i]);
            i++;
        } 
        else {
            newArr.push_back(arr2[j]);
            j++;
        }
    }

    while (i < n) {
        newArr.push_back(arr1[i]);
        i++;
    }

    while (j < m) {
        newArr.push_back(arr2[j]);
        j++;
    }

    // step 2: find median of the sorted array.

    int size = newArr.size();
    int pos = size-1;
    double median = -1.0;

    if (size % 2 == 0) {
        double first = static_cast<double>(newArr[pos/2]);
        double second = static_cast<double>(newArr[(pos/2) + 1]);
        median = (first + second) / 2.0;
    } 
    else {
        median = static_cast<double>(newArr[pos/2]);
    }

    return median;
}

// Approach 3: Using Binary Search (VI)
// Time Complexity: O(min(log N, log M))
// Space Complexity: O(1)

double median(vector<int>& arr1, vector<int>& arr2) {
    // step 1: we always start from small size array so if arr2 is smaller we have to 
    // start with smaller

    if (arr2.size() < arr1.size()) {
        return median(arr2, arr1);
    }

    // step 2: now, arr1 is smaller size array apply binary search for partitioning

    int n = arr1.size();
    int m = arr2.size();

    // partition variables for arr1 (smaller array)
    int low = 0;
    int high = n;

    while (low <= high) {
        int cut1 = low + (high - low)/2; 
        // we are doing partition by taking first cut1 elements from arr1

        int cut2 = ((n + m + 1)/2) - cut1; 
        // remaining cut2 number of elements taken from arr2

        int left1 = (cut1 == 0) ? INT_MIN : arr1[cut1-1];
        // if we takes 0 elements from start in arr1, last element of left partitioned 
        // array will be INT_MIN

        int left2 = (cut2 == 0) ? INT_MIN : arr2[cut2-1];
        // if we take 0 remaining elements from start in arr2, last element will be 
        // INT_MIN.

        int right1 = (cut1 == n) ? INT_MAX : arr1[cut1];
        // if we partition at last in arr1, right1 will be INT_MAX
        int right2 = (cut2 == m) ? INT_MAX : arr2[cut2];
        // if we partition at last in arr2, right2 will be INT_MAX

        if (left1 <= right2 && left2 <= right1) {
            // now check, is the final sorted array size is even or odd
            if ((n + m) % 2 == 0) {
                return (max(left1, left2) + min(right1, right2)) / 2.0;
            }
            else {
                return max(left1, left2);
            }
        }
        else if (left1 > right2) { 
            // if left1 is bigger than right2, we have to remove one element from 
            // arr1 by moving back.
            high = cut1 - 1;
        }
        else {
            low = cut1 + 1;
        }
    }

    return 0.0;
}
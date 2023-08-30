#include <iostream>
#include <vector>
using namespace std;

// This problem is similar to Median of Two Sorted Arrays

// Approach 1: Brute Force using Merge Two Sorted Arrays.
// Time Complexity: O(N)
// Space Complexity: O(N)

int kthElementInTwoSortedArrays(vector<int> &arr1, vector<int> &arr2, int n, int m, int k) {
    if (k > n + m) {
        return -1;
    }

    // step 1: merge both arrays arr1 and arr2 using two pointer approach
    
    int i = 0;
    int j = 0;

    vector<int> finalVec;
    while (i < n && j < m) {
        if (arr1[i] < arr2[j]) {
            finalVec.push_back(arr1[i]);
            i++;
        }
        else {
            finalVec.push_back(arr2[j]);
            j++;
        }
    }

    while (i < n) {
        finalVec.push_back(arr1[i]);
        i++;
    }

    while (j < m) {
        finalVec.push_back(arr2[j]);
        j++;
    }

    // step 2: after merging both arrays return k-1 value of new sorted array.

    return finalVec[k - 1];
}

// Approach 2: Two Pointer Approach
// Time Complexity: O(K)
// Space Complexity: O(1)

int kthElementinTwoSortedArrays(vector<int> &row1, vector<int> &row2, int n, int m, int k) {
    // if none of the case return -1, in case of k > n + m
    if (k > n + m) {
        return -1;
    }
    
    // step 1: traverse both arrays using Two Pointer Approach
    
    int i = 0;
    int j = 0;

    int count = 0;
    // keep count for checking the kth element

    while (i < n && j < m) {
        // if count is k - 1, means we reached at the position where we have to 
        // return the minimum of both array at current.

        if (count == k-1) {
            return min(row1[i], row2[j]);
        }
        
        if (row1[i] < row2[j]) { // if row1[i] is less move ahead and increase count
            count++;
            i++;
        }
        else { // if row2[j] is less move ahead and increase count
            count++;
            j++;
        }
    }

    // step 3: if any of i or j reached to end of row1 or row2. Check the count 
    // while incrementing in remaining part of row1 or row2

    while (i < n) {
        if (count == k-1) { // if count becomes k - 1, return the current element
            return row1[i];
        }
        count++;
        i++;
    }

    while (j < m) {
        if (count == k-1) { // if count becomes k - 1, return the current element
            return row2[j];
        }
        count++;
        j++;
    }
}

// Approach 3: Binary Search (VI)
// Time Complexity: O(min(Log N, Log M))
// Space Complexity: O(1)

int kthElementinTwoSortedArrays(vector<int> &row1, vector<int> &row2, int n, int m, int k) {
    // step 1: check if size of first arr is big, so switch the arrays and do the binary
    // search on smaller array
    
    if (n > m) {
        return kthElementInTwoSortedArrays(row2, row1, m, n, k);
    }

    // We have to mention these constaints in assigning the iterators because, 
    // for example: if we have two arrays
    // arr1 = {7, 12, 14, 15}, size = 4
    // arr2 = {1, 2 , 3, 4, 9, 11}, size = 6

    // case 1: if k = 3
    // minimum elements we can pick from arr1 is 0 and maximum can pick is 3
    // because we get the answer from left half itself
    // so we make high = min(k, n) because if k is smaller than n, we have to take
    // k elements from arr1 like above case we have to take 3 elements from arr1 due to
    // k = 3 not k = 4.

    // case 2: if k = 7
    // maximum elements we can pick from arr1 is atleast 1 because in arr2, we have 
    // only 6 elements and for making the left half equal to 7. Thats why, minimum 
    // elements can be pick from 1 i.e. k - m (m is size of second array).

    // step 2: make the iterators for making two parts using row1 and row2

    int low = max(0, k - m);
    int high = min(n, k);

    while (low <= high) {
        int cut1 = low + (high - low)/2;
        // apply cut1 in smaller array at cut1 ahead from starting

        int cut2 = k - cut1;
        // In median of two sorted arrays, question k = middle element i.e 
        // (n + m + 1)/2 when we getting answer from left half.

        int left1 = (cut1 == 0) ? INT_MIN : row1[cut1-1];
        // if we apply cut1 at 0, means not taking any element from row1 hence left1
        // is INT_MIN

        int left2 = (cut2 == 0) ? INT_MIN : row2[cut2 - 1];
        // if we apply cut2 at 0, means not taking any element from row2 hence left2
        // is INT_MIN

        int right1 = (cut1 == n) ? INT_MAX : row1[cut1];
        // if we apply cut1 at 0, means not taking any element from row1 hence right1
        // is INT_MAX

        int right2 = (cut2 == m) ? INT_MAX : row2[cut2];
        // if we apply cut2 at 0, means not taking any element from row2 hence right2
        // is INT_MAX

        if (left1 <= right2 && left2 <= right1) {
            // left1 is smaller than right2 and left2 is smaller than right1, we got
            // correct set of row1 and row2 and we can take max of both as kth Element
            return max(left1, left2);
        } 
        else if (left1 > right2) {
            // if left1 is bigger, need to decrease left1 so move backward.
            high = cut1 - 1;
        }
        else {
            // if left2 is smaller, need to increase left1 so move ahead.
            low = cut1 + 1;
        }
    }
    
    return 1;
}
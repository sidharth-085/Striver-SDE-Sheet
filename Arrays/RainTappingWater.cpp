#include <iostream>
using namespace std;

// Approach 1: Brute Force
// Time Complexity: O(N^2)
// Space Complexity: O(1).

long long getTrappedWater1(long long *arr, int size) {
    long long totalWater = 0;

    for (int i=0; i<size; i++) {
        long long leftMax = arr[i];

        // Find the maximum height to the left of the current element
        for (int j=i; j>=0; j--) {
            leftMax = max(leftMax, arr[j]);
        }

        long long rightMax = arr[i];

        // Find the maximum height to the right of the current element
        for (int j=i; j < size; j++) {
            rightMax = max(rightMax, arr[j]);
        }

        long long currWater = min(leftMax, rightMax) - arr[i];

        totalWater = totalWater + currWater;
    }
    
    return totalWater;
}

// Approach 2: Better approach using Prefix Max Array & Suffix Max Array
// Time Complexity : O(N)
// Space Complexity: O(2N)

// Before understanding this approach, we need to know Prefix max array & Suffix max array.

long long getTrappedWater2(long long *arr, int size) {
    // Create a prefix max array
    long long *prefixMax = new long long[size];
    prefixMax[0] = arr[0];

    for (int i=1; i<size; i++) {
        // Calculate the maximum height to the left of the current element
        prefixMax[i] = max(prefixMax[i-1], arr[i]);
    }

    // Create a suffix max array
    long long *suffixMax = new long long[size];
    suffixMax[size-1] = arr[size-1];

    for (int i=size-2; i>=0; i--) {
        // Calculate the maximum height to the right of the current element
        suffixMax[i] = max(suffixMax[i+1], arr[i]);
    }

    long long totalWater = 0;

    for (int i=0; i<size; i++) {
        // Calculate the trapped water at each element using prefix and suffix max arrays
        long long currWater = min(prefixMax[i], suffixMax[i]) - arr[i];
        totalWater = totalWater + currWater;
    }

    return totalWater;
}

// Approach 3: Most Optimal Solution to save memory from O(2N) to O(N).
// Time Complexity : O(N)
// Space Complexity: O(1)

long long getTrappedWater3(long long *arr, int size) {
    int left = 0;
    int right = size - 1;

    long long leftMax = 0, rightMax = 0, totalWater = 0;

    while (left < right) {
        if (arr[left] <= arr[right]) {
            // Process the left side of the array

            if (arr[left] >= leftMax) {
                leftMax = arr[left];
            }
            else {
                // Calculate the trapped water at the current element
                long long currWater = leftMax - arr[left];
                totalWater = totalWater + currWater;
            }
            left++;
        }
        else {
            // Process the right side of the array

            if (arr[right] >= rightMax) {
                rightMax = arr[right];
            }
            else {
                // Calculate the trapped water at the current element
                long long currWater = rightMax - arr[right];
                totalWater = totalWater + currWater;
            }
            right--;
        }
    }
    
    return totalWater;
}
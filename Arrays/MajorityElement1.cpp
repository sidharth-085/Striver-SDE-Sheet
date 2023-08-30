#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Here, we have to find the element having frequency more than N/2

// whenever question is saying, finding those elements which have freq more than N/M 
// only M-1 numbers are there in array 

// Brute Force Approach

// Time Complexity: O(N*N)
// Space Complexity: O(1)

int findMajorityElement(int arr[], int n) {
    for (int i=0; i<n; i++) {
        int maxCount = 1; // initially every elemenet has count 1

        for (int j=i+1; j<n; j++) {
            if (arr[j] == arr[i]) {
                maxCount++;
            }
        }

        if (maxCount > floor(n/2)) {
            return arr[i];
        }
    }
    return -1;
}

// Approach using Hashmap
// Time Complexity: O(N)
// Space Complexity: O(N)

int findMajorityElement(int arr[], int n) {
	unordered_map<int, int> map;
	for (int i=0; i<n; i++) {
		map[arr[i]]++;
	}

	for (auto &it : map) {
		if (it.second > floor(n/2)) {
			return it.first;
		}
	}
	return -1;
}

// Approach using Boyer-moore Majority Vote Algorithm

// Time Complexity: O(N)
// Space Complexity: O(1)

int findMajorityElement(int arr[], int n) {	
	// Variable to store the majority element in the array, it it is present.
	int majorityElement = -1;
	int count = 0;

	// Iterating the array to know if there is a possible majority element present.
	for(int i = 0; i < n; i++) {	
		// If count becomes 0, set current element as a possible candidate for majority element, reset count to 1.
		if(count == 0) {
			majorityElement = arr[i];
			count = 1;
			continue;
		}

		// Increment the count if the current element of the array is equal to the current majority element, else decrement it.
		if(arr[i] == majorityElement) {
			count++;
		}		
		else {
			count--;
		}
	}

	count = 0;

	// Checking if majority element occurs more than 'n' / 2 times.
	for(int i = 0; i < n; i++) {
		if(arr[i] == majorityElement) {
			count++;
		}
	}

	// If the count of the majority element is greater than 'n' / 2, then return it.
	if(count > floor(n / 2)) {
		return majorityElement;
	}

	// If no majority element found, return -1.
	return -1;	
}
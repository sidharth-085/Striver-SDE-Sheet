#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Brute Force Approach
// Time Complexity: O(N^2)
// Space Complexity: O(1)

// this approach is simple, first we find the repeat element and then calculate sum of
// all elements present in arr and (1 to n). Then, first we subtract the duplicate once
// element we get the sum in which one element is missing. Finally, we subtract total
// sum which has that missing element and we get the missing element.

pair<int,int> missingAndRepeating(vector<int> &arr, int n) {
	int repeat = -1;
	int missing = -1;
    
    // find repeating element

	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (arr[i] == arr[j]) {
				repeat = arr[i];
				break;
			}
		}
	}

    // total sum formula 

	int totalSum = n * (n + 1)/2;

    // find sum of all elements present in array

	int currSum = 0;

	for (int i=0; i<n; i++) {
		currSum = currSum + arr[i];
	}

    // then find sum after removing repeating element once and then get the missing
    // element

    int removeRepeat = currSum - repeat;
    missing = totalSum - removeRepeat;

	return {missing, repeat};
}

// Approach 2: Better Approach using Sorting
// Time Complexity: O(N * Log N)
// Space Complexity: O(1)

// Here, we find the repeating element using sorting and comparing the element in pairs

pair<int,int> missingAndRepeating(vector<int> &arr, int n) {
	int repeat = -1;
	int missing = -1;

    // sort the array and then find the repeating element

	sort(arr.begin(), arr.end());

	for (int i=0; i<n-1; i++) {
		if (arr[i] == arr[i+1]) {
			repeat = arr[i];
			break;
		}
	}

	// total sum formula 

	int totalSum = n * (n + 1)/2;

    // find sum of all elements present in array

	int currSum = 0;

	for (int i=0; i<n; i++) {
		currSum = currSum + arr[i];
	}

	// then find sum after removing repeating element once and then get the missing
    // element

    int removeRepeat = currSum - repeat;
    missing = totalSum - removeRepeat;

	return {missing, repeat};
}

// Approach 3: Optimal Approach using extra space
// Time Complexity: O(N)
// Space Complexity: O(N)

pair<int,int> missingAndRepeating(vector<int> &arr, int n) {
	int repeat = -1;
	int missing = -1;

	vector<int> numFreq(n+1, 0);
    // make a vector to store frequencies of every element of arr

	for (int i=0; i<n; i++) { // increment the frequency of every element
		numFreq[arr[i]]++;
	}

    // now check from 1 to n, which element has frequency 0, means it is missing one
    // and which one have frequency greater than 1, that will be repeat one.

	for (int num=1; num<=n; num++) {
		if (numFreq[num] == 0) {
			missing = num;
		}
		else if (numFreq[num] > 1) {
			repeat = num;
		}
	}

	return {missing, repeat};
}

// Approach 4: Optimal Approach without using extra space (Bit Manupulation)
// Time Complexity: O(N)
// Space Complexity: O(1)

// This method involves some steps listed below:
// 1. First we have to find XOR of all the elements of arr and 1 to N together

// 2. By doing XOR of all elements of arr and 1 to N, all the elements of arr are 
//    cancelled by elements from 1 to N, only duplicate element from arr and missing
//    element from 1 to N remains and we have XOR of both remaining element.

// 3. So, after after finding the XOR, find the first bit index from last which is set
//    because if a bit is set, two numbers which we want are differ by one bit because
//    XOR of opposite bits is 1 always.

// 4. When we got the first bit index from last which is set. Now, we take XOR of those 
//    elements in arr which has set bit on same position where we found the set bit in 
//    XOR and those elements which has clear bit bit on same separately.

// 5. Now, we take XOR of those numbers from 1 to n has set bit on same position 
//    where we found the set bit in XOR and those numbers which has clear bit bit on 
//    same separately.

// 6. After taking XOR for setBit and notSetBit. We will get two element out of which
//    one is repeating other is missing. To find this, traverse the array and check 
//    bitSet and notBit set which occurs in array, any of them occurs in arr, means it 
//    repeating and other is missing one.

pair<int,int> missingAndRepeating(vector<int> &arr, int n) {
    int XOR = 0;

    // step 1

    for (int i=0; i<n; i++) {
        XOR = XOR ^ arr[i];
        XOR = XOR ^ (i + 1);
    }

    // step 2

    int bitIndex = XOR & ~(XOR-1);

    // step 3

    int bitSet = 0; int bitNotSet = 0;

    for (int i=0; i<n; i++) {
        if (arr[i] & bitIndex) {
            bitSet = bitSet ^ arr[i];
        }
        else {
            bitNotSet = bitNotSet ^ arr[i];
        }
    }

    // step 4

    for (int i=1; i<=n; i++) {
        if (i & bitIndex) {
            bitSet = bitSet ^ i;
        }
        else {
            bitNotSet = bitNotSet ^ i;
        }
    }

    // step 5

    int missing = -1;
    int repeat = -1;

    for (int i=0; i<n; i++) {
        if (bitSet == arr[i]) {
			repeat = bitSet;
			missing = bitNotSet;
			break;
		}

		if (bitNotSet == arr[i]) {
			repeat = bitNotSet;
			missing = bitSet;
			break;
		}
    }

    return {missing, repeat};
}
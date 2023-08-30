#include <iostream>
#include <unordered_map>
using namespace std;

// Brute Force: Find all subarrays and take xor, and if x matches with current xor,
// increase the count

// Time Complexity: O(N*N)
// Space Complexity: O(1)

int subarraysXor(vector<int> &arr, int k) {
    int count = 0;
    int size = arr.size();

    for (int i=0; i<size; i++) {
        int XOR = 0; // start with zero for different indexes
        for (int j=i; j<size; j++) {
            XOR = XOR ^ arr[j]; // take xor with current element
            if (XOR == k) {
                count++;
            }
        }
    }
    return count;
}

// Optimal Approach using Hashmaps

// Time Complexity: O(N)
// Space Complexity: O(N)

// step 1: first find the xor till ith index named prefixXor till every ith index.
// step 2: Is there any subarray ending at ith index having xor sum k, then x ^ k = 
// prefixXor. Therefore, x = prefixXor ^ k
// step 3: count how many subarray from starting have XOR 'x' and add to the count
// step 4: finally insert the current prefixXor till ith into map with increases its 
// frequency.

int subarraysXor(vector<int> &arr, int k) {
    int count = 0;

    unordered_map<int, int> map; // stores all the prefix xors count

    int prefixXor = 0;

    for (int i=0; i < arr.size(); i++) {
        prefixXor = prefixXor ^ arr[i];

        int required = k ^ prefixXor;

        count = count + map[required];

        map[prefixXor]++;
    }

    return count;
}
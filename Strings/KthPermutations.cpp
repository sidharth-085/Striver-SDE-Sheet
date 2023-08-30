#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// In this question, we are given two integers n and k. n represents the string from
// number "1" to "n". We have to return the kth Permutation of string made from integer
// n if all the permutations are in sorted order.

// Approach 1: Brute Force Approach
// Time Complexity: O(N! * Log N!)
// Space Complexity: O(N!)

// for finding all the permutations, it takes O(N!) time, and this generates N! 
// permutations, now we sort the N! permutations so time complexity is O(N! * Log N!).

// general function for finding the permutations of the string and add to the 
// permutations vector
void findPermutations(string &str, int si, int n, vector<string> &permutations) {
    if (si == n) {
        permutations.push_back(str);
        return;
    }

    for (int i=si; i<n; i++) {
        swap(str[si], str[i]);

        findPermutations(str, si+1, n, permutations);

        swap(str[si], str[i]);
    }
}

string kthPermutation(int n, int k) {
    string str = "";

    // first make the string from n i.e. "123......n"

    for (int i=1; i<=n; i++) {
        str.push_back(i + '0');
    }

    // now call the findPermutations function and find all permutations

    vector<string> permutations;

    findPermutations(str, 0, n, permutations);

    // now sort all the permutations

    sort(permutations.begin(), permutations.end());

    // finally return kth permutation from sorted permutations

    return permutations[k-1];
}

// Approach 2: Optimal Approach
// Time Complexity: O(N! * Log N!)
// Space Complexity: O(N!)

// In this approach, we will follow a different method which is given as steps below:

// 1. Step 1: Firstly, we decide which of the following num from 1 to N is our first 
// number for the kth Permutation.

// 2. Step 2: We can decide this with the help of using (k / fact) this will tell which
// num should be the first character of the kth permutation. Here fact is factorial of
// one less than current n i.e. (n-1)!, because when we take the first num, we are left 
// with n-1 numbers which have different permutations at max (n-1)!. 

// 3. Step 3: After getting the number which is becoming our first num, we will erase it
// using erase function of vector.

// 4. Step 4: Then we check if size of vector holding nums for which we have to decide
// permutation.

// 5. Step 5: At last, we update k with k % fact which tell it that which permuation we 
// have to take from remaining nums in vector and update fact with dividing with current 
// remaining nums size means (n-1)! will become (n-2)! and so on.

string kthPermutation(int n, int k) {
    int fact = 1;

    string ans = "";
    vector<int> nums;

    for (int i=1; i<n; i++) {
        fact = fact * i;
        nums.push_back(i);
    }

    nums.push_back(n); // keep all numbers from 1 to n
    k = k - 1;
    // decrease k because we will find the answer using 0 based indexing

    while (true) {
        int permutationGroup = k/fact;
        ans.append(to_string(nums[permutationGroup]));
        nums.erase(nums.begin() + permutationGroup);
        
        if (nums.size() == 0) {
            break;
        }

        k = k % fact;
        fact = fact/nums.size();
    }

    return ans;
}
#include <iostream>
using namespace std;

// In this question we are using the concept of binary exponentiation. Binary
// Exponentiation is the function to calculate the a ^ b without going out of limits

// Approach 1: Brute Force Approach 
// Time Complexity: O(N)
// Space Complexity: O(N)

int modularExponentiation(int x, int n, int mod) {
    int ans = 1;

    for (int i = 0; i < n; i++) {
        ans = (ans * 1LL * x) % mod; // use 1LL for doing calculation in long long
    }

    return ans;
}

// Approach 2: Recursive Approach 
// Time Complexity: O(Log N)
// Space Complexity: O(Log N)

int modularExponentiation(int x, int n, int mod) {
    if (n == 0) {
        return 1;
    }

    int result = modularExponentiation(x, n/2, mod);

    if (n & 1) { // new way to check is n is odd or not
        // if n is odd, means we have to separate x and find the answer for odd using 
        // recursion

        return (x * ((result * 1LL * result) % mod)) % mod;

        // multiplying 1LL to make current calculation in long long and finally 
        // taking mod to make answer within limits
    }
    else {
        // if n is even we can call recursion and find the answer
        return (result * 1LL * result) % mod;

        // multiplying 1LL to make current calculation in long long and finally 
        // taking mod to make answer within limits
    }   
}

// Approach 3: Using Iterative Approach
// Time Complexity: O(log N)
// Space Complexity: O(log N)

int modularExponentiation(int x, int n, int mod) {
    int ans = 1;

    // this approach is similar to recursion but little different, here we are going
    // to use bits to get the answer

    // we convert n to its binary representation and then multply its corresponding
    // value in the power of 2.
    // for example: for 6 ^ 7
    // we take 7 and write its binary representation as 1 1 0 1
    // now we can also write 6 ^ 13 = 6 ^ (8 + 4 + 0 + 1) {multiplying 1 with power of 2}
    // now we can write 6 ^ 7 = (6 ^ 8) + (6 ^ 4) + (6 ^ 0) + (6 ^ 1)

    while (n > 0) {
        if (n & 1) { // here we are checking the last bit of n is this 1 or not
            ans = (ans * 1LL * x) % mod;
            // if it is one multiply x with ans and take mod
        }
        x = (x * 1LL * x) % mod; 
        // then update the x with next power of x and repeat this process
        n = n >> 1;
        // now right shift the n by 1 for checking next bit
    }

    return ans; // finally return the answer
}
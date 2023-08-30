#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Rabin-Karp algorithm is used for pattern search, we use hash function in this code
// for the string.

// We take the previous hashValue, multiply with 256 for next character. Then add next char
// to it. And finally, to reduce value within bounds we use % prime number (101) in our case.
// We can take any prime number 

// Time Complexity: O(P+T)

vector<int> stringMatch(string txt, string pat) {
    vector<int> res;

    int d = 256; // No of characters in input
    int prime = 101; // Prime number to do mod operation
    int patSize = pat.length();
    int textSize = txt.length();

    if (patSize > textSize) {
        return res;
    }

    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < patSize - 1; i++) {
        h = (h * d) % prime;
    }

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < patSize; i++) {
        p = (d * p + pat[i]) % prime;
        t = (d * t + txt[i]) % prime;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= textSize - patSize; i++) {
        // Check the hash values of current window of text and pattern
        // If the hash values match, then only check for characters one by one
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < patSize; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }

            // If p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == patSize) {
                res.push_back(i+1);
            }
        }

        // Calculate hash value for the next window of text
        // Remove leading digit, add trailing digit
        if (i < textSize - patSize) {
            t = (d * (t - txt[i] * h) + txt[i + patSize]) % prime;

            // We might get negative values of t, converting it to positive
            if (t < 0) {
                t = t + prime;
            }
        }
    }

    return res;
}
#include <iostream>
using namespace std;

// In this question, we are given two version numbers as two strings we have to check
// which one is newer version

// Approach 1: Using Iterative Approach 
// Time Complexity: O(N + M)
// Space Complexity: O(N)

int compareVersions(string str1, string str2) {
    int i = 0; // pointer for version 1
    int j = 0; // pointer for version 2

    while (i < str1.size() || j < str2.size()) {
        long long num1 = 0; long long num2 = 0;
        // variables for calculating number before the dot

        // traverse the version 1 code till dot and find the number
        while (i < str1.size() && str1[i] != '.') {
            num1 = (num1 * 10) + (str1[i] - '0');
            i++;
        }   
        // traverse the version 2 code till dot and find the number
        while (j < str2.size() && str2[j] != '.') {
            num2 = (num2 * 10) + (str2[j] - '0');
            j++;
        }

        if (num1 > num2) { // if version1 is bigger than version2, answer is 1
            return 1; 
        }
        else if (num1 < num2) { // if version2 is bigger than version1, answer is -1
            return -1;
        }
        else { // if we get dot, just move one ahead
            i++;
            j++;
        }
    }

    return 0; // finally if both are identical return 0.
}
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

// Method 1: Brute Force using Sort

// Time Complexity: O(n*Logn)
// Space Complexity: O(1)

bool areAnagram(string &str1, string &str2){
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());
    return str1 == str2;
}

// Method 2: Using Hashmap
// Time Complexity: O(n)
// Space Complexity: O(n)

bool areAnagram(string &str1, string &str2){
    if (str1.size() != str2.size()) {
        return false;
    }

    unordered_map<char, int> map;

    for (int i=0; i<str1.size(); i++) {
        map[str1[i]]++;
    }

    for (int i=0; i<str2.size(); i++) {
        if (map.find(str2[i]) == map.end()) {
            return false;
        }
    }

    return true;
}

// Method 3: Using Hashing without Maps

// Time Complexity: O(n)
// Space Complexity: O(1)

bool areAnagram(string &str1, string &str2){
    // Create a count array and initialize all values as 0.
    int hash[256] = { 0 };
    int i;

    int n1 = str1.length();
    int n2 = str2.length();
    // If length of both strings is not same, then they cannot be anagram.
    if (n1 != n2){
       return false;
    }

    /*
       For each character in input strings, 
       increment count in the corresponding count array.
    */
    for (i = 0; i < n1; i++){
        hash[str1[i]]++;
        hash[str2[i]]--;
    }

    // Check if all values in hash array are 0.
    for (i = 0; i < 256; i++){
        if (hash[i] != 0){
            return false;
        }
    }
    return true;
}
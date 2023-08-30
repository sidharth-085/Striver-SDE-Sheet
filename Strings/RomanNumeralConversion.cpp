#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Approach 1: Recursion 
// Time Complexity: O(N)
// Space Complexity: O(N)

int romanToIntHelper(string s, unordered_map<string, int> &conv) {
    // If single character, return the integer value of that character.
    if (s.size() <= 1) {
        return conv[s];
    }
    // Take first 2 characters.
    string first_two = s.substr(0, 2);

    // If the first 2 characters are in the map, add their value and check rest of the string.
    if (conv.find(first_two) != conv.end()) {
        return conv[first_two] + romanToIntHelper(s.substr(2, s.size() - 2), conv);
    }
    else {
        // otherwise take one character and check its value.
        return conv[s.substr(0, 1)] + romanToIntHelper(s.substr(1, s.size() - 1), conv);
    }
}
int romanToInt(string s) {
    unordered_map<string, int> conv {
        {"M", 1000},
        {"D", 500},
        {"C", 100},
        {"L", 50},
        {"X", 10},
        {"V", 5},
        {"I", 1},
        {"IV", 4},
        {"IX", 9},
        {"XL", 40},
        {"XC", 90},
        {"CD", 400},
        {"CM", 900},
        {"", 0}};
    return romanToIntHelper(s, conv);
}

// Appoach 2: Using Hashmap without Recursion
// Time Complexity: O(N)
// Space Complexity: O(1)
// N is length of string

int romanToInt(string s) {
    unordered_map<char, int> map;

    map.insert({'I', 1});
    map.insert({'V', 5});
    map.insert({'X', 10});
    map.insert({'L', 50});
    map.insert({'C', 100});
    map.insert({'D', 500});
    map.insert({'M', 1000});

    int ans = 0;

    for (int i=0; i<s.size(); i++) {
        if (map[s[i]] < map[s[i+1]]) { 
            // if first letter have lesser value than next one, we have to substact the answer
            ans = ans - map[s[i]];
        }
        else { // else add to answer
            ans = ans + map[s[i]];
        }
    }
    return ans; // finally return answer
}
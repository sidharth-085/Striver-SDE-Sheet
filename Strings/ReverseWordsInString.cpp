#include <iostream>
#include <string>
using namespace std;

// it is the basic code we have to remove the trail spaces also. So approach is little different.

// Brute Force Approach

string reverseString(string &str) {
    int n = str.length();
	string ans;
	int i = 0;

	while (i < n) {
	    int j = i;

		// Skip multiple spaces.
		while (j < n && str[j] == ' ') {
			j++;
		}

		string currentWord;

		// Get the current word.
		while (j < n && str[j] != ' ') {
			currentWord.push_back(str[j]);
			j++;
		}

		// Add current word in the ans with a space.
		if (currentWord.length() != 0) {
			ans.insert(0, currentWord + " ");
		}

		i = j + 1;
	}

	if (ans.length() == 0) {
		return ans;
	}

	// Remove the last space.
	return ans.substr(0, ans.length() - 1);
} 

// Optimal Solution

string reverseString(string &str) {
    int start = str.size() - 1;

    string output;

    while (start >= 0) {
        if (str[start] == ' ') {
            start--; // Skip trailing spaces
        }
        else {
            if (output.size() > 0) {
                output.push_back(' '); // Add space between words
            }

            int j = start;
            while (j >= 0 && str[j] != ' ') {
                j--; // Find the start index of the current word
            }

            // Append the current word to the output
            output.append(str.substr(j + 1, start - j));

            start = j; // Move start to the next word
        }
    }

    return output;
}
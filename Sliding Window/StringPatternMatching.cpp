#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Using Substring Method
// Time Complexity: O(N)
// Space Complexity: O(1)

vector<int> zAlgorithm(string str, string pat, int strLen, int patLen) {
    vector<int> ans; // this array stores the indices where we get the pattern in str

    for (int i=0; i<(strLen-patLen+1); i++) {
        string substr = str.substr(i, patLen);
        // find the substring for every index with length patLen

        if (substr == pat) { // if it matches with pat, match is found at current index
            ans.push_back(i); // add that index to ans.
        }
    }    

    return ans;
}

// Approach 2: Using Sliding Window Method
// Time Complexity: O(N)
// Space Complexity: O(1)

vector<int> zAlgorithm(string str, string pat, int strLen, int patLen) {
    vector<int> ans; // this array stores the indices where we get the pattern in str

    string slidingStr = ""; // string which holds the substring of length patLen

    for (int i=0; i<patLen; i++) { // iterate for first window of length patLen
        slidingStr.push_back(str[i]);
    }

    // if first window matches with pat, add the 0th index to ans.

    if (slidingStr == pat) {
        ans.push_back(0);
    }

    // now starts iteration for every window, where i denotes the last index of curr
    // window

    for (int i=patLen; i < strLen; i++) {
        slidingStr.erase(slidingStr.begin()); 
        // remove the first character from sliding string

        slidingStr.push_back(str[i]);
        // add the last character of current window in sliding string

        if (slidingStr == pat) { // now match both strings, if matched add its index
            ans.push_back(i);
        }
    }    

    return ans;
}

// Approach 3: Z-Algorithm
// Time Complexity: O(N + M)
// Space Complexity: O(N + M)

// str = ababa
// pat = ab
// 			 0 1 2 3 4 5 6 7
// new_string = a b # a b a b a

vector<int> zAlgorithm(string str, string pat, int n, int m) {
	vector<int> ans; // this array stores the indices where we get the pattern in str

    // step 1: first make the newStr which holds pattern and string with a special 
    // character which divides both strings 

	string newStr = pat + '#' + str;
	int len = newStr.size();

    // step 2: now create a z vector which holds the length till which pattern matches
    // in string str
	
	vector<int> z(len);
	
	for (int i=0; i<len; i++) {
        // step 3: from 0th index to pattern length, add 0 in the z vector, because
        // we have to compare the pattern in string str

		if (i <= m) {
			z[i] = 0;
			continue;
		}

        // step 4: if i >= (patLen + 1) which is string str in which we have to find
        // pattern pat, we check is 0th and ith character matches or not
		
		int count = 0;
		
		if (newStr[0] == newStr[i]) {
            // if they matches start from it and traverse till when start and end 
            // not matches

			int start = 0; // always starts from 0 (due to pattern)
			int end = i; // start from i where we found match
			
			while (newStr[start] == newStr[end]) {
				count++; // increase the count everytime when start and end matches

				start++;
				end++;
			}
		}

        // now we get the length which matches with pat, now add this to the z array.

		z[i] = count;
	}

    // step 5: now iterate the complete new string and check if any value in z array
    // is equal to the patLen, add the (index - patLen - 1) for getting correct index
    // for string str 

	for (int i=0; i<len; i++) {
		if (z[i] == m) {
			ans.push_back(i - m - 1);
		}
	}

	return ans;
    // finally returns the occurences index of pattern in string str.
}
#include <iostream>
#include <string>
using namespace std;

// The problem is little different. In this question, we have to count the particular
// num character and write it frequency and the number together as string
// Base case is given: if n == 1, str = "1"
// for n == 2, str = "11" (one times one)
// for n == 3, str = "21" (two times one)
// for n == 4, str = "1211" (one time two, one time one) and so on
 
// Approach 1: With Recursion
// Time Complexity: O(M * M)
// Space Complexity: O(M)

// M is the length of string for given N

string writeAsYouSpeak(int n) {
    // step 1: base case if n == 1

    if (n == 1) {
        return "1";
    }

    // step 2: find the answer for n - 1

    string ans = writeAsYouSpeak(n - 1);

    // step 3: now make an empty string and append the frequency and character side by
    // side in temp string

    string temp = "";
    int i = 0;
    // iterator to keep travelling in the ans string

    while (i < ans.size()) {
        int count = 1; // for every character, atleast frequency should be 1
        
        // run the while loop till the consecutive characters are not equal
        while (i < (ans.size() - 1) && ans[i] == ans[i+1]) {
            count++; // increment the frequency
            i++; // move pointer ahead
        }

        // step 4: append the count at the starting and number after it

        temp.append(to_string(count));
        temp.push_back(ans[i]);
        
        i++;
        // move the pointer to right for next character
    }

    return temp;
}

// Approach 2: Iterative Approach 
// Time Complexity: O(M * M)
// Space Complexity: O(M)

string writeAsYouSpeak(int n) {
    // step 1: base case string which is "1"
    string str = "1";

    // step 2: after first base case, remaiing iterations are n - 1

    int iterations = n-1;

    // step 3: traverse the iterations and decreasing iterations one by one

    while (iterations > 0) {
        vector<int> count;
        // frequency array count for keeping freq for every num character

        string temp = "";
        // temporary string for storing numbers which are not repeating

        int i = 0;
		while (i < str.size()) {
			int cnt = 1; // for every character, atleast frequency should be 1
            
            // run the while loop till the consecutive characters are not equal
			while (i < (str.size() - 1) && str[i] == str[i+1]) {
				cnt++; // increment the frequency
				i++; // move pointer ahead
			}

            // step 4: add the count to the count array which stores frequency for every
            // character and append the numbers to the temp string

			count.push_back(cnt);
			temp.push_back(str[i]);
			i++;
		}

        // step 5: now, make the string str empty and append all the frequency along
        // with the corresponding number to the string str

        str = "";

        for (int i=0; i<temp.size(); i++) {
            str.append(to_string(count[i]));
            str.push_back(temp[i]);
        }

        iterations--;
        // decrease the iterations
    }

    return str;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Brute Force : O(N^3) Time Complexity

vector<string> returnAllSubstrings(string str) {
    int size = str.size();
    vector<string> ans;

    // pick starting point
    for (int len = 1; len <= size; len++) {
        // pick ending point
        for (int i=0; i<=size-len; i++) {
            string output = "";
            int j = (i + len) - 1;
            for (int k=i; k<=j; k++) {
                output = output + str[k];
            }
            ans.push_back(output);
        }
        
    }
    return ans;
} 

// Optimal solution using substr() function
// Time complexity: O(N^2)

vector<string> returnAllSubstrings(string str) {
    int size = str.size();
    vector<string> ans;

    for (int i=0; i<size; i++) {
        for (int len = 1; len <= size - i; len++) {
            string output = str.substr(i, len);
            ans.push_back(output);
        }
    }
    return ans;
}

int main() {
    vector<string> ans = returnAllSubstrings("abcd");
    for (int i=0; i<ans.size(); i++) {
        cout << ans[i] << endl;
    }
}
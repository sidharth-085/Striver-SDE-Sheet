#include <iostream>
#include <vector>
#include <string>
using namespace std;

void findPermutationsHelper(string &str, int start, int end, vector<string> &ans) {
    if (start == end) {
        // when we reached at end, add the string to ans
        ans.push_back(str);
        return;
    }

    // now we are traversing every char and swap each time to get the answer
    for (int i=start; i<=end; i++) {
        // first swap ith & start character
        swap(str[i], str[start]);
        // now call the helper function from start + 1.
        findPermutationsHelper(str, start + 1, end, ans);
        // now backtracking and keep the character at its orignal position
        swap(str[i], str[start]);
    }
}

vector<string> findPermutations(string &str) {
    vector<string> ans;
    findPermutationsHelper(str, 0, str.size() - 1, ans);
    return ans;
}
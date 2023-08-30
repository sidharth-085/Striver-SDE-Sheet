#include <iostream>
#include <vector>
using namespace std;

// We need to find the next permutation for given array.

// Approach 1: Recursion with sorting

// Time Complexity: O(N*N!)
// Space Complexity: O(N*N)

void permutations(vector<int> permutation, int n, int si, vector<vector<int>> &ans) {
    if (si == n) {
        ans.push_back(permutation); // when reached at end, add into answer
        return;
    } 

    for (int i=si; i < n; i++) {
        swap(permutation[si], permutation[i]); // swap the curr element with starting element

        permutations(permutation, n, si+1, ans); // call recursion to get answer

        swap(permutation[si], permutation[i]); // backtrack to go for next permutation
    }
}

vector<int> nextPermutation(vector<int> &permutation, int n) {
    vector<vector<int>> ans;

    permutations(permutation, n, 0, ans);

    sort(ans.begin(), ans.end()); 
    // once we get the all permutations, we can sort it for lexicographical order

    for (int i = 0; i < ans.size(); i++) {
        if (i == ans.size() - 1) { 
            // if we reached at end, there will be first permutation which will be next
            return ans[0];
        }
        if (ans[i] == permutation) { 
            // and if permutation matches with ans[i], return next one.
            return ans[i+1];
        }
    }
}

// Approach 2: Better approach using STL function next_permutation(begin, end)
// Time Complexity: O(N)
// Space Complexity: O(1)

vector<int> nextPermutation(vector<int> &permutation, int n) {
    next_permutation(permutation.begin(), permutation.end());
    // this functions changes the given vector into its next permutation
    return permutation;
}

// Approach 3: Optimal Solution (Greedy Solution)
// Time Complexity: O(N)
// Space Complexity: O(1)

void reverse(vector<int> &arr, int start, int end) {
    int i = start;
    int j = end;

    while (start <= end) {
        swap(arr[start], arr[end]);
        start++;
        end--; 
    }
}

vector<int> nextPermutation(vector<int> &permutation, int n) {
    // step 1: first we have to find the index where the element is smaller than its next

    int index = -1;
    for (int i = n-2; i >= 0; i--) {
        if (permutation[i] < permutation[i+1]) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        reverse(permutation, 0, n-1);
        return permutation;
    }

    // step 2: we got the index, where the partition is to be done
    // now we have to find the element index which is just greater than element at (index)

    for (int i = n-1; i >= index; i--) {
        if (permutation[i] > permutation[index]) {
            swap(permutation[i], permutation[index]);
            break;
        }
    }

    // step 3: no we swapped and got the just greater element at correct position
    // now we have to just reverse the array and we will get the answer

    reverse(permutation, index + 1, n - 1);
    return permutation;
}
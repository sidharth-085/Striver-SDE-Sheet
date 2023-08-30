#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// In this question, we have to return those elements which have frequency more than
// floor of N/3 as vector.

// whenever question is saying, finding those elements which have freq more than N/M 
// only M-1 numbers are there in array 

// Approach 1: Brute Force Approach (little tricky to understand)
// Time Complexity: O(N^2)
// Space Complexity: O(1)

vector<int> majorityElementII(vector<int> &arr) {
    vector<int> ans;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int freq = 1; // initially the freq of every element is 1
        for (int j = i + 1; j < n; j++) { // start from one ahead
            if (arr[i] == arr[j]) { 
                freq++;
            }
        }

        if (freq > floor(n/3)) { // if freq is bigger than n/3
            // if ans is empty or if ans is not empty check the size should be less 
            // than 2 to insert the element && last element should not be equal to 
            // current to be insert element, because when we are finding element having
            // frequency more than n/3 only 2 elements can be present in ans

            if (ans.size() == 0 || (ans.size() < 2 && ans.back() != arr[i])) {
                ans.push_back(arr[i]);
            }
        }
    }

    return ans;
}

// Approach 2: Using Sorting (approach same as duplicate element problem)
// Time Complexity: O(N * Log N)
// Space Complexity: O(1)

vector<int> majorityElementII(vector<int> &arr) {
    sort(arr.begin(), arr.end());

    vector<int> ans;
    
    int n = arr.size();
    for (int i=0; i<n; i++) {
        int freq = 1;
        while (i < n && arr[i] == arr[i+1]) {
            freq++;
            i++;
        }

        if (freq > floor(n/3)) {
            ans.push_back(arr[i]);
        }
    }

    return ans;
}

// Approach 3: Using HashMap for frequency
// Time Complexity: O(N)
// Space Comlexity: O(N)

vector<int> majorityElementII(vector<int> &arr) {
    vector<int> ans;

    unordered_map<int, int> freq;

    for (int i=0; i<arr.size(); i++) {
        freq[arr[i]]++;
    }

    for (auto &it : freq) {
        if (it.second > floor(arr.size()/3)) {
            ans.push_back(it.first);
        }
    }

    return ans;
}

// Approach 3: Using Sorting (approach same as duplicate element problem)
// Time Complexity: O(N * Log N)
// Space Complexity: O(1)

vector<int> majorityElementII(vector<int> &arr) {
    sort(arr.begin(), arr.end());

    vector<int> ans;
    
    int n = arr.size();
    for (int i=0; i<n; i++) {
        int freq = 1;
        while (i < n && arr[i] == arr[i+1]) {
            freq++;
            i++;
        }

        if (freq > floor(n/3)) {
            ans.push_back(arr[i]);
        }
    }

    return ans;
}

// Approach 4: Boyer-Moore Majority Vote Algorithm
// Time Complexity: O(N)
// Space Complexity: O(1)

vector<int> majorityElementII(vector<int> &arr) {
    vector<int> ans;

    // step 1: for freq elements n/3 only 2 elements can exists

    int first = 0; // first candidate
    int second = 0; // second candidate

    int firstFreq = 0;
    int secondFreq = 0;

    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (arr[i] == first) { 
            // if current element is first candidate, increase freq
            firstFreq++;
        }
        else if (arr[i] == second) { 
            // if current element is second candidate, increase freq
            secondFreq++;
        }
        else if (firstFreq == 0) { // if first frequency is 0, add to first element
            first = arr[i];
            firstFreq++;
        }
        else if (secondFreq == 0) { // if second frequency is 0, add to second element
            second = arr[i];
            secondFreq++;
        }
        else { 
            // if there is diff element than both first and second, decrease the freq 
            // of both candidats
            firstFreq--;
            secondFreq--;
        }
    }

    // step 2: now we got the potential candidates for majority elements, check the
    // current first and second have freq more than n/3, if yes add to answer

    firstFreq = 0;
    secondFreq = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == first) {
            firstFreq++;
        }
        else if (arr[i] == second) {
            secondFreq++;
        }
    }

    if (firstFreq > floor(n/3)) {
        ans.push_back(first);
    }

    if (secondFreq > floor(n/3)) {
        ans.push_back(second);
    }

    return ans;
}
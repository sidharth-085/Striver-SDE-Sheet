#include <iostream>
using namespace std;

// We have an array, we have to find the maximum XOR with any two elements in given array.

// Brute Force 1: 

// Time Complexity: O(N*N)
// Space Complexity: O(1)

int maximumXor(vector<int> arr) {
    int n = arr.size();

    int maxAns = 0;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            maxAns = max(maxAns, arr[i] ^ arr[j]);
        }
    }
    
    return maxAns;
}

// Approach 2: Using Tries & Bit Manupulation

// Time Complexity: O(N)

class TrieNode { // class for trie node
    TrieNode* children[2];

    public: 

    bool containsKey(int bit) {
        return children[bit] != NULL;
    }

    TrieNode* get(int bit) {
        return children[bit];
    } 

    void put(int bit) {
        children[bit] = new TrieNode();
    }
};

class Trie {
    TrieNode *root;

    public:

    Trie() {
        root = new TrieNode();
    }

    void insert(int num) { // insertion of every bit from left to right
        TrieNode *temp = root;
        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1; // right shift the num to i bit with and 1 gives that bit
            if (temp->containsKey(bit) == false) { // if bit is not present make a new node there
                temp->put(bit);
            }
            temp = temp->get(bit); // update the temp with current bit
        }
    }

    int max_xor(int num) {
        TrieNode *temp = root;
        int ans = 0;

        for (int i=31; i>=0; i--) {
            int bit = (num >> i) & 1; // get the bit again
            if (temp->containsKey(!bit) == true) { 
				// check for opposite bit, because for XOR operation we get 1 only if 
				// there is 1 zero present, then if we have 0 we need 1 & vice versa, so 
				// find the oposite bit 
                
				ans = ans | (1 << i); // if opposite bit is there, update the ith bit of ans with 1
                temp = temp->get(!bit); // and update temp to opposite bit
            }
            else {
                temp = temp->get(bit); // if it does not have opposite bit, update temp with current bit. 
            }
        }

        return ans; // finally return the answer
    }

};

int maximumXor(vector<int> arr) {
    Trie trie;

    int n = arr.size();

    for (int i=0; i<n; i++) {
        trie.insert(arr[i]);
    }

    int maxAns = 0;

    for (int i=0; i<n; i++) {
        int maxXor = trie.max_xor(arr[i]);
        maxAns = max(maxAns, maxXor);
    }

    return maxAns;
}
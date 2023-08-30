#include <iostream>
using namespace std;

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